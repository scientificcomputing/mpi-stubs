FROM ubuntu:24.04 AS dev-env

ARG ADIOS2_VERSION=2.11.0
ARG DOXYGEN_VERSION=1_14_0
ARG GMSH_VERSION=4_15_0
ARG HDF5_VERSION=2.0.0
ARG KAHIP_VERSION=3.21
ARG NUMPY_VERSION=2.3.5
ARG PETSC_VERSION=3.24.2
ARG SLEPC_VERSION=3.24.1
ARG SPDLOG_VERSION=1.16.0

# Compiler optimisation flags for SLEPc and PETSc.
ARG PETSC_SLEPC_OPTFLAGS="-O2"
ARG PETSC_SLEPC_DEBUGGING="yes"
ARG BUILD_NP=4

WORKDIR /tmp

ENV OPENBLAS_NUM_THREADS=1 \
    OPENBLAS_VERBOSE=0 \
    DEBIAN_FRONTEND=noninteractive

# --- 1. Base APT Dependencies ---
RUN apt-get -qq update && \
    apt-get -yq --with-new-pkgs -o Dpkg::Options::="--force-confold" upgrade && \
    apt-get -y install \
    cmake g++ gfortran \
    libboost-dev liblapack-dev libopenblas-dev libpugixml-dev \
    ninja-build pkg-config python3-dev python3-pip python3-venv \
    catch2 git graphviz libeigen3-dev valgrind wget \
    libglu1 libxcursor-dev libxft2 libxinerama1 libfltk1.3-dev \
    libfreetype6-dev libgl1-mesa-dev libocct-foundation-dev libocct-data-exchange-dev \
    bison flex && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# --- 2. Build and Install the MPI Stub ---
ENV STUBS_DIR=/opt/mpistubs
# Inject stub wrappers directly into PATH so all downstream builds find mpicc naturally
ENV PATH="${STUBS_DIR}/bin:${PATH}"

COPY . /tmp/mpi-stubs
RUN cd /tmp/mpi-stubs && \
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${STUBS_DIR} && \
    cmake --build build -j ${BUILD_NP} && \
    cmake --install build && \
    ldconfig ${STUBS_DIR}/lib && \
    rm -rf /tmp/*

# --- 3. Python Virtual Environment ---
ENV VIRTUAL_ENV=/dolfinx-env
ENV PATH=/dolfinx-env/bin:$PATH
RUN python3 -m venv ${VIRTUAL_ENV} && \
    pip install --no-cache-dir --upgrade pip "setuptools<74" wheel && \
    pip install --no-cache-dir cython numpy==${NUMPY_VERSION}

# Install mpi4py against our stub
RUN env MPI4PY_BUILD_MPIABI=1 MPICC="${STUBS_DIR}/bin/mpicc" \
    pip install --no-cache-dir --no-build-isolation --no-binary mpi4py mpi4py

RUN python3 -c "from mpi4py import MPI; print(MPI.Get_version())" && \
    python3 -c "import numpy; print(numpy.__version__)"

# --- 4. System Libraries (Spdlog, Doxygen, KaHIP, HDF5, ADIOS2, GMSH) ---
RUN wget -nc --quiet https://github.com/gabime/spdlog/archive/refs/tags/v${SPDLOG_VERSION}.tar.gz && \
    tar xfz v${SPDLOG_VERSION}.tar.gz && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DSPDLOG_BUILD_SHARED=ON -DSPDLOG_BUILD_PIC=ON -B build-dir -S spdlog-${SPDLOG_VERSION} && \
    cmake --build build-dir && cmake --install build-dir && rm -rf /tmp/*

RUN wget -nc --quiet https://github.com/doxygen/doxygen/archive/refs/tags/Release_${DOXYGEN_VERSION}.tar.gz && \
    tar xfz Release_${DOXYGEN_VERSION}.tar.gz && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -B build-dir -S doxygen-Release_${DOXYGEN_VERSION} && \
    cmake --build build-dir && cmake --install build-dir && rm -rf /tmp/*

# Install KaHIP
RUN wget -nc --quiet https://github.com/kahip/kahip/archive/v${KAHIP_VERSION}.tar.gz && \
    tar -xf v${KAHIP_VERSION}.tar.gz && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
          -DNONATIVEOPTIMIZATIONS=on \
          -DCMAKE_C_COMPILER=mpicc \
          -DCMAKE_CXX_COMPILER=mpicxx \
          -B build-dir -S KaHIP-${KAHIP_VERSION} && \
    cmake --build build-dir && \
    cmake --install build-dir && \
    rm -rf /tmp/*

# HDF5 uses our mpicc natively because it is in the PATH
RUN wget -nc --quiet https://github.com/HDFGroup/hdf5/archive/refs/tags/hdf5_${HDF5_VERSION}.tar.gz && \
    tar xfz hdf5_${HDF5_VERSION}.tar.gz && \
    cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release \
          -DHDF5_ENABLE_PARALLEL=on -DHDF5_ENABLE_Z_LIB_SUPPORT=on \
          -DCMAKE_C_COMPILER=mpicc -DCMAKE_CXX_COMPILER=mpicxx \
          -B build-dir -S hdf5-hdf5_${HDF5_VERSION} && \
    cmake --build build-dir && cmake --install build-dir && rm -rf /tmp/*

RUN wget -nc --quiet https://github.com/ornladios/ADIOS2/archive/v${ADIOS2_VERSION}.tar.gz -O adios2-v${ADIOS2_VERSION}.tar.gz && \
    mkdir -p adios2-v${ADIOS2_VERSION} && tar -xf adios2-v${ADIOS2_VERSION}.tar.gz -C adios2-v${ADIOS2_VERSION} --strip-components 1 && \
    cmake -G Ninja -DADIOS2_USE_HDF5=on -DCMAKE_INSTALL_PYTHONDIR=/usr/local/lib/ -DADIOS2_USE_Fortran=off -DBUILD_TESTING=off -DADIOS2_BUILD_EXAMPLES=off -DADIOS2_USE_ZeroMQ=off -DCMAKE_C_COMPILER=mpicc -DCMAKE_CXX_COMPILER=mpicxx  -B build-dir -S ./adios2-v${ADIOS2_VERSION} && \
    cmake --build build-dir && cmake --install build-dir && rm -rf /tmp/*

RUN git clone -b gmsh_${GMSH_VERSION} --single-branch --depth 1 https://gitlab.onelab.info/gmsh/gmsh.git && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DENABLE_BUILD_DYNAMIC=1 -DENABLE_OPENMP=1 \
          -DCMAKE_C_COMPILER=mpicc -DCMAKE_CXX_COMPILER=mpicxx \
          -B build-dir -S gmsh && \
    cmake --build build-dir && cmake --install build-dir && rm -rf /tmp/*
ENV PYTHONPATH=/usr/local/lib:$PYTHONPATH

# --- 5. Install PETSc (Single Arch: real64-32) ---
ENV PETSC_DIR=/usr/local/petsc 
ENV SLEPC_DIR=/usr/local/slepc

RUN git clone --depth=1 -b v${PETSC_VERSION} https://gitlab.com/petsc/petsc.git ${PETSC_DIR} && \
    cd ${PETSC_DIR} && \
    ./configure \
    PETSC_ARCH=linux-gnu-real64-32 \
    --COPTFLAGS="${PETSC_SLEPC_OPTFLAGS}" \
    --CXXOPTFLAGS="${PETSC_SLEPC_OPTFLAGS}" \
    --FOPTFLAGS="${PETSC_SLEPC_OPTFLAGS}" \
    --with-64-bit-indices=no \
    --with-debugging="${PETSC_SLEPC_DEBUGGING}" \
    --with-fortran-bindings=no \
    --with-shared-libraries \
    --with-mpi-dir="${STUBS_DIR}" \
    --with-scalar-type=real \
    --with-precision=double \
    --download-hypre \
    --download-metis \
    --download-mumps-avoid-mpi-in-place \
    --download-mumps \
    --download-ptscotch \
    --download-scalapack \
    --download-spai \
    --download-suitesparse \
    --download-superlu \
    --download-superlu_dist && \
    make PETSC_ARCH=linux-gnu-real64-32 all && \
    cd src/binding/petsc4py && \
    PETSC_ARCH=linux-gnu-real64-32 pip -v install --no-cache-dir --no-build-isolation . && \
    cd ${PETSC_DIR} && \
    rm -rf **/tests/ **/obj/ **/externalpackages/ CTAGS RDict.log TAGS docs/ share/ src/ systems/ /tmp/*

# --- 6. Install SLEPc (Single Arch: real64-32) ---
RUN git clone --depth=1 -b v${SLEPC_VERSION} https://gitlab.com/slepc/slepc.git ${SLEPC_DIR} && \
    cd ${SLEPC_DIR} && \
    export PETSC_ARCH=linux-gnu-real64-32 && \
    ./configure && \
    make && \
    cd src/binding/slepc4py && \
    PETSC_ARCH=linux-gnu-real64-32 pip -v install --no-cache-dir --no-build-isolation . && \
    cd ${SLEPC_DIR} && \
    rm -rf CTAGS TAGS docs/ src/ **/obj/ **/test/ /tmp/*


# --- 7. FEniCSx Toolchain (Basix, UFL, FFCx) ---
# ARG DOLFINX_CMAKE_BUILD_TYPE="Release"
ARG DOLFINX_CMAKE_BUILD_TYPE="Developer"
ENV PETSC_ARCH=linux-gnu-real64-32

RUN git clone https://github.com/FEniCS/basix.git /tmp/basix && \
    cd /tmp/basix/cpp && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=${DOLFINX_CMAKE_BUILD_TYPE} \
    -DCMAKE_C_COMPILER=mpicc -DCMAKE_CXX_COMPILER=mpicxx \
    -B build-dir -S . && \
    cmake --build build-dir && cmake --install build-dir && \
    cd ../python && pip install --no-cache-dir . && \
    rm -rf /tmp/*

RUN git clone https://github.com/FEniCS/ufl.git /tmp/ufl && \
    cd /tmp/ufl && pip install --no-cache-dir . && \
    git clone https://github.com/FEniCS/ffcx.git /tmp/ffcx && \
    cd /tmp/ffcx && pip install --no-cache-dir . && \
    rm -rf /tmp/*

    
# --- 8. Build DOLFINx (from local repository context) ---
RUN git clone https://github.com/FEniCS/dolfinx.git /dolfinx
# We explicitly override FindMPI variables so CMake doesn't try to invoke `mpicc --showme`
RUN cd /dolfinx/cpp && \
    PETSC_ARCH=linux-gnu-real64-32 cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/usr/local/dolfinx-real \
          -DCMAKE_BUILD_TYPE=${DOLFINX_CMAKE_BUILD_TYPE} \
          -DCMAKE_C_COMPILER=mpicc -DCMAKE_CXX_COMPILER=mpicxx \
          -DPETSC_DIR=/usr/local/petsc \
          -DDOLFINX_ENABLE_PETSC=ON -DDOLFINX_ENABLE_SLEPC=ON -DDOLFINX_ENABLE_SCOTCH=ON -DDOLFINX_ENABLE_KAHIP=ON -DDOLFINX_ENABLE_ADIOS2=ON \
          -B build-dir -S . && \
    cmake --build build-dir -j ${BUILD_NP} && \
    cmake --install build-dir && \
    cd ../python && \
    pip install --no-cache-dir scikit-build-core && \
    python -m scikit_build_core.build requires | python -c "import sys, json; print(' '.join(json.load(sys.stdin)))" | xargs pip install --no-cache-dir && \
    PETSC_ARCH=linux-gnu-real64-32 CC=mpicc CXX=mpicxx pip install \
        --config-settings=cmake.define.CMAKE_C_COMPILER=mpicc \
        --config-settings=cmake.define.CMAKE_CXX_COMPILER=mpicxx \
        --config-settings=cmake.build-type="${DOLFINX_CMAKE_BUILD_TYPE}" --config-settings=install.strip=false --no-build-isolation --check-build-dependencies \
        --target /usr/local/dolfinx-real/lib/python${PYTHON_VERSION}/dist-packages --no-dependencies --no-cache-dir '.' && \
    rm -rf /dolfinx/cpp/build-dir

ENV PKG_CONFIG_PATH=/usr/local/dolfinx-real/lib/pkgconfig:$PKG_CONFIG_PATH \
    CMAKE_PREFIX_PATH=/usr/local/dolfinx-real/lib/cmake:$CMAKE_PREFIX_PATH \
    PETSC_ARCH=linux-gnu-real64-32 \
    PYTHONPATH=/usr/local/dolfinx-real/lib/python${PYTHON_VERSION}/dist-packages:$PYTHONPATH \
    LD_LIBRARY_PATH=/usr/local/dolfinx-real/lib:$LD_LIBRARY_PATH

WORKDIR /root