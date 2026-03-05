cmake_minimum_required(VERSION 3.5.0...4.1.0)
project(mpi-abi-stubs VERSION 5.0 LANGUAGES C)

option(BUILD_SHARED_LIBS "Build libraries as SHARED" TRUE)

add_library(mpi_abi mpi.c)
set_target_properties(mpi_abi PROPERTIES VERSION 0)
set_target_properties(mpi_abi PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)

include(GNUInstallDirs)
install(FILES mpi.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS mpi_abi DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Create standard CMake namespace aliases
add_library(MPI::MPI_C ALIAS mpi_abi)
add_library(MPI::MPI_CXX ALIAS mpi_abi)

# Generate wrappers

# Use $0 to resolve the base directory at runtime so scripts are relocatable in Python wheels
set(SCRIPT_BASE "#!/bin/sh\nDIR=\"$( cd \"$( dirname \"$0\" )/..\" && pwd )\"\n")

set(WRAPPER_SCRIPT_C "${SCRIPT_BASE}exec \"${CMAKE_C_COMPILER}\" -I\"$DIR/${CMAKE_INSTALL_INCLUDEDIR}\" \"$@\" -L\"$DIR/${CMAKE_INSTALL_LIBDIR}\" -Wl,-rpath,\"$DIR/${CMAKE_INSTALL_LIBDIR}\" -lmpi_abi\n")
set(WRAPPER_SCRIPT_CXX "${SCRIPT_BASE}exec \"${CMAKE_CXX_COMPILER}\" -I\"$DIR/${CMAKE_INSTALL_INCLUDEDIR}\" \"$@\" -L\"$DIR/${CMAKE_INSTALL_LIBDIR}\" -Wl,-rpath,\"$DIR/${CMAKE_INSTALL_LIBDIR}\" -lmpi_abi\n")
set(WRAPPER_SCRIPT_FC "${SCRIPT_BASE}exec gfortran -I\"$DIR/${CMAKE_INSTALL_INCLUDEDIR}\" \"$@\" -L\"$DIR/${CMAKE_INSTALL_LIBDIR}\" -Wl,-rpath,\"$DIR/${CMAKE_INSTALL_LIBDIR}\" -lmpi_abi\n")

# Copy the physical mpiexec script and FORCE Unix line endings (LF)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/bin/mpiexec ${CMAKE_CURRENT_BINARY_DIR}/mpiexec NEWLINE_STYLE LF)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/mpicc ${WRAPPER_SCRIPT_C})
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/mpicxx ${WRAPPER_SCRIPT_CXX})
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/mpif90 ${WRAPPER_SCRIPT_FC})


# Ensure the generated scripts are executable
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/mpicc PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/mpicxx PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/mpif90 PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/mpiexec PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

# ==============================================================================
# INSTALLATION
# ==============================================================================

install(TARGETS mpi_abi
    EXPORT MPIStubTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES 
    mpi.h 
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
