
# MPI Stubs

A lightweight, ABI-compliant mock implementation of the Message Passing Interface (MPI) for compiling and running MPI applications in a serial (single-process) environment.

This package provides the essential C, C++, and Fortran headers (`mpi.h`, `mpif.h`), a dummy shared library (`libmpi.so`), and standard compiler wrappers (`mpicc`, `mpicxx`, `mpif90`, `mpiexec`)—all conveniently installable via `pip`.

## 🚀 Why use `mpi-stubs`?
Many scientific computing libraries (e.g., PETSc, SLEPc, HDF5, FEniCSx, KaHIP) have hard dependencies on MPI. When you only need to run these libraries serially or want to build a minimal Docker image/CI pipeline, installing a full MPI implementation (like OpenMPI or MPICH) adds unnecessary bloat, compilation time, and complexity.

`mpi-stubs` solves this by providing:

* **Drop-in Compiler Wrappers**: `mpicc`, `mpicxx`, and `mpif90` are provided and automatically link against the dummy MPI library.

* **Mock Executable**: A mock `mpiexec` / `mpirun` command that safely ignores MPI arguments (like `-n 4`) and simply executes the program serially.

* **Broad Compatibility**: Implements Point-to-Point, Collectives, Attribute Caching (required by PETSc), and File I/O (required by HDF5).

* **Python Integration**: Easily installable via `pip` using the `scikit-build-core` backend, making it perfect for building `mpi4py` or other Python bindings in a serial context.

## 📦 Installation

You can install `mpi-stubs` directly via pip. This will compile the stubs and place the compiler wrappers directly in your Python environment's `PATH`.

```bash
# Clone the repository
git clone [https://github.com/yourusername/mpi-stubs.git](https://github.com/yourusername/mpi-stubs.git)
cd mpi-stubs

# Install via pip
pip install .
```

*Note: You will need CMake and a C/C++/Fortran compiler installed on your system to build the package.*

## 🛠️ Usage

Once installed, the MPI wrapper scripts behave exactly like their real counterparts.

### Compiling Code

You can use `mpicc`, `mpicxx`, and `mpif90` directly from your terminal:

```bash
mpicc my_mpi_code.c -o my_program
```

Behind the scenes, these wrappers intercept the call, attach the correct include paths to `mpi.h`, link `libmpi.so`, and pass the rest of the arguments to your system's underlying compiler (e.g., `gcc` or `clang`).

### Running Code

You can run your compiled program normally or use the packaged `mpiexec`:

```bash
mpiexec -n 4 ./my_program
```

*Note: Because this is a stub environment, `mpiexec` simply strips the `-n 4` arguments and runs `./my_program` as a standard, single-process executable. `MPI_Comm_size` will always return `1`, and `MPI_Comm_rank` will always return `0`.*

### Using with CMake

If you are building a CMake project that calls `find_package(MPI)`, ensure your Python environment is active. CMake will automatically discover the `mpicc` and `mpicxx` compilers in your `PATH` and configure your project to build against the stubs.

## ⚙️ Implementation Details

* **Communicators & Ranks**: All valid communicators map to a size of 1 and a rank of 0.

* **Point-to-Point (P2P)**: `MPI_Send` and `MPI_Recv` act as direct memory copies (`memcpy`) between buffers since both source and destination are rank 0.

* **Collectives**: Operations like `MPI_Bcast`, `MPI_Allreduce`, and `MPI_Gather` execute locally, applying reductions or copies in-place. Non-blocking collectives (MPI-3) are supported and instantly resolve.

* **Persistent Requests**: Supported (MPI-4.0+ compliant).

* **File I/O**: `MPI_File_*` operations are mapped directly to standard POSIX/C file operations (`open`, `read`, `write`, `pread`, `pwrite`).

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.
