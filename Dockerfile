FROM ubuntu:24.04 AS dev-env

ARG DOXYGEN_VERSION=1_14_0
ARG SPDLOG_VERSION=1.16.0
ARG NUMPY_VERSION=2.3.5
ARG PETSC_VERSION=3.24.2
ARG GMSH_VERSION=4_15_0
ARG HDF5_VERSION=2.0.0
ARG BUILD_NP=4
ARG PETSC_SLEPC_OPTFLAGS="-O2"

WORKDIR /tmp

ENV OPENBLAS_NUM_THREADS=1 \
    OPENBLAS_VERBOSE=0 \
    DEBIAN_FRONTEND=noninteractive

# --- 1. Install System Dependencies ---
# Note: Added libhdf5-dev so FEniCSx has a serial HDF5 backend available
RUN apt-get -qq update && \
    apt-get -yq --with-new-pkgs -o Dpkg::Options::="--force-confold" upgrade && \
    apt-get -y install \
    cmake \
    g++ \
    gfortran \
    libboost-dev \
    liblapack-dev \
    libopenblas-dev \
    libpugixml-dev \
    ninja-build \
    pkg-config \
    python3-dev \
    python3-pip \
    python3-venv \
    catch2 \
    git \
    graphviz \
    libeigen3-dev \
    valgrind \
    wget \
    libglu1 \
    libxcursor-dev \
    libxft2 \
    libxinerama1 \
    libfltk1.3-dev \
    libfreetype6-dev \
    libgl1-mesa-dev \
    libocct-foundation-dev \
    libocct-data-exchange-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/*

# --- 2. Install spdlog ---
RUN wget -nc --quiet https://github.com/gabime/spdlog/archive/refs/tags/v${SPDLOG_VERSION}.tar.gz && \
    tar xfz v${SPDLOG_VERSION}.tar.gz && \
    cd spdlog-${SPDLOG_VERSION} && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DSPDLOG_BUILD_SHARED=ON -DSPDLOG_BUILD_PIC=ON -B build-dir . && \
    cmake --build build-dir && \
    cmake --install build-dir && \
    rm -rf /tmp/*

# --- 3. Python Virtual Environment ---
ENV VIRTUAL_ENV=/dolfinx-env
ENV PATH=/dolfinx-env/bin:$PATH
RUN python3 -m venv ${VIRTUAL_ENV} && \
    pip install --no-cache-dir --upgrade pip "setuptools<70.0.0" wheel && \
    pip install --no-cache-dir cython "numpy==${NUMPY_VERSION}"

# --- 4. Build and Install MPI Stub ---
COPY . /tmp/mpi-stubs
RUN cd /tmp/mpi-stubs && \
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j ${BUILD_NP} && \
    cmake --install build && \
    ldconfig && \
    rm -rf /tmp/*


RUN wget -nc --quiet https://github.com/HDFGroup/hdf5/archive/refs/tags/hdf5_${HDF5_VERSION}.tar.gz && \
    tar xfz hdf5_${HDF5_VERSION}.tar.gz && \
    cd hdf5-hdf5_${HDF5_VERSION} && \
    cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/usr/local \
          -DCMAKE_BUILD_TYPE=Release \
          -DHDF5_ENABLE_PARALLEL=ON \
          -DHDF5_ENABLE_Z_LIB_SUPPORT=ON \
          -DMPI_C_COMPILER=cc \
          -DMPI_CXX_COMPILER=c++ \
          -DMPI_C_INCLUDE_DIRS=/usr/local/include \
          -DMPI_C_LIBRARIES=/usr/local/lib/libmpi.so \
          -DMPI_CXX_INCLUDE_DIRS=/usr/local/include \
          -DMPI_CXX_LIBRARIES=/usr/local/lib/libmpi.so \
          -B build-dir -S . && \
    cmake --build build-dir -j ${BUILD_NP} && \
    cmake --install build-dir && \
    rm -rf /tmp/*


# --- 5. Install mpi4py against the stub ---
# We force mpi4py's setup.py to use the standard C compiler and explicitly pass our stub locations.
RUN env MPICC=cc CFLAGS="-I/usr/local/include" LDFLAGS="-L/usr/local/lib -lmpi" \
    pip install --no-cache-dir --no-build-isolation mpi4py

# # --- 6. Install PETSc and petsc4py ---
# ENV PETSC_DIR=/usr/local/petsc SLEPC_DIR=/usr/local/slepc
# RUN git clone --depth=1 -b v${PETSC_VERSION} https://gitlab.com/petsc/petsc.git ${PETSC_DIR} && \
#     cd ${PETSC_DIR} && \
#     ./configure \
#     PETSC_ARCH=linux-gnu-real64-32 \
#     --COPTFLAGS="${PETSC_SLEPC_OPTFLAGS}" \
#     --CXXOPTFLAGS="${PETSC_SLEPC_OPTFLAGS}" \
#     --with-64-bit-indices=no \
#     --with-debugging=no \
#     --with-fc=0 \
#     --with-cc=cc \
#     --with-cxx=c++ \
#     --with-mpi=1 \
#     --with-mpi-include=/usr/local/include \
#     --with-mpi-lib=/usr/local/lib/libmpi.so \
#     --with-shared-libraries=1 \
#     --download-suitesparse \
#     --download-superlu \
#     --with-scalar-type=real \
#     --with-precision=double && \
#     make PETSC_ARCH=linux-gnu-real64-32 ${MAKEFLAGS} all && \
#     cd src/binding/petsc4py && \
#     PETSC_ARCH=linux-gnu-real64-32 pip -v install --no-cache-dir --no-build-isolation . && \
#     rm -rf ${PETSC_DIR}/**/tests/ ${PETSC_DIR}/**/obj/ ${PETSC_DIR}/src/ /tmp/*


# --- 7. FEniCSx Toolchain (Basix, UFL, FFCx) ---
RUN git clone https://github.com/FEniCS/basix.git /tmp/basix && \
    cd /tmp/basix/cpp && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -B build-dir -S . && \
    cmake --build build-dir && cmake --install build-dir && \
    cd ../python && pip install --no-cache-dir . && \
    rm -rf /tmp/*

RUN git clone https://github.com/FEniCS/ufl.git /tmp/ufl && \
    cd /tmp/ufl && pip install --no-cache-dir . && \
    git clone https://github.com/FEniCS/ffcx.git /tmp/ffcx && \
    cd /tmp/ffcx && pip install --no-cache-dir . && \
    rm -rf /tmp/*

    
# # --- 8. Build DOLFINx (from local repository context) ---
# RUN git clone https://github.com/FEniCS/dolfinx.git /dolfinx
# # We explicitly override FindMPI variables so CMake doesn't try to invoke `mpicc --showme`
# RUN cd /dolfinx/cpp && \
#     cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/usr/local \
#           -DCMAKE_BUILD_TYPE=Release \
#           -DMPI_C_COMPILER=cc \
#           -DMPI_CXX_COMPILER=c++ \
#           -DMPI_C_INCLUDE_DIRS=/usr/local/include \
#           -DMPI_C_LIBRARIES=/usr/local/lib/libmpi.so \
#           -DMPI_CXX_INCLUDE_DIRS=/usr/local/include \
#           -DMPI_CXX_LIBRARIES=/usr/local/lib/libmpi.so \
#           -DPETSC_DIR=/usr/local/petsc \
#           -DPETSC_ARCH=linux-gnu-real64-32 \
#           -B build-dir -S . && \
#     cmake --build build-dir -j ${BUILD_NP} && \
#     cmake --install build-dir && \
#     cd ../python && \
#     pip install --no-cache-dir . && \
#     rm -rf /dolfinx/cpp/build-dir

WORKDIR /root