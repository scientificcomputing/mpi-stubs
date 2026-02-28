cmake_minimum_required(VERSION 3.15)
project(mpistub LANGUAGES C CXX Fortran)

# Source files
set(MPI_STUB_SOURCES src/mpi.c src/mpi.f90)

# Tell CMake where to put the generated .mod file during build and install
set(CMAKE_Fortran_MODULE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/mod)

# Build as a shared library
add_library(mpistub SHARED ${MPI_STUB_SOURCES})

# Force the output name to "mpi" to generate libmpi.so
set_target_properties(mpistub PROPERTIES
    OUTPUT_NAME "mpi"
    VERSION "1.0.0"
    SOVERSION "1"
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
)

# Setup include directories
target_include_directories(mpistub PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Create standard CMake namespace aliases
add_library(MPI::MPI_C ALIAS mpistub)
add_library(MPI::MPI_CXX ALIAS mpistub)

include(GNUInstallDirs)

# ==============================================================================
# WRAPPER GENERATION
# ==============================================================================

# Notice "$@" is placed BEFORE the linker flags (-L and -lmpi)
set(WRAPPER_SCRIPT_C "#!/bin/sh\nexec \"${CMAKE_C_COMPILER}\" -I\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}\" \"$@\" -L\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\" -Wl,-rpath,\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\" -lmpi\n")

set(WRAPPER_SCRIPT_CXX "#!/bin/sh\nexec \"${CMAKE_CXX_COMPILER}\" -I\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}\" \"$@\" -L\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\" -Wl,-rpath,\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\" -lmpi\n")

set(WRAPPER_SCRIPT_FC "#!/bin/sh\nexec gfortran -I\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}\" \"$@\" -L\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\" -Wl,-rpath,\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\" -lmpi\n")

# Safely strip out -n / -np arguments so the serial binary executes normally
set(WRAPPER_SCRIPT_EXEC "#!/bin/sh\nwhile [ $# -gt 0 ]; do\n  case \"$1\" in\n    -n|-np) shift 2 ;;\n    *) break ;;\n  esac\ndone\nexec \"$@\"\n")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/mpicc ${WRAPPER_SCRIPT_C})
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/mpicxx ${WRAPPER_SCRIPT_CXX})
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/mpif90 ${WRAPPER_SCRIPT_FC})
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/mpiexec ${WRAPPER_SCRIPT_EXEC})

# Ensure the generated scripts are executable
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/mpicc PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/mpicxx PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/mpif90 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/mpiexec PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

# ==============================================================================
# INSTALLATION
# ==============================================================================

install(TARGETS mpistub
    EXPORT MPIStubTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES 
    include/mpi.h 
    include/mpif.h 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(PROGRAMS 
    ${CMAKE_CURRENT_BINARY_DIR}/mpicc
    ${CMAKE_CURRENT_BINARY_DIR}/mpicxx
    ${CMAKE_CURRENT_BINARY_DIR}/mpif90
    ${CMAKE_CURRENT_BINARY_DIR}/mpiexec
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/mod/ 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} 
        OPTIONAL)

# --- Testing ---
enable_testing()
add_executable(test_mpi_stub tests/test_mpi_stub.c)
target_link_libraries(test_mpi_stub PRIVATE MPI::MPI_C)
add_test(NAME MPIStubSanityCheck COMMAND test_mpi_stub)