cmake_minimum_required(VERSION 3.15)
project(mpistub LANGUAGES C CXX)

# Source files
set(MPI_STUB_SOURCES
    src/mpi.c
)

# Build as a shared library so mpi4py and FEniCSx can load it dynamically
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
    $<INSTALL_INTERFACE:include>
)

# Create standard CMake namespace aliases
add_library(MPI::MPI_C ALIAS mpistub)
add_library(MPI::MPI_CXX ALIAS mpistub)

# Provide modern installation rules
include(GNUInstallDirs)
install(TARGETS mpistub
    EXPORT MPIStubTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(FILES 
    include/mpi.h 
    include/mpif.h 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# --- Testing ---
enable_testing()

add_executable(test_mpi_stub tests/test_mpi_stub.c)
# Link against the ALIAS we created earlier to ensure correct include paths and ABI
target_link_libraries(test_mpi_stub PRIVATE MPI::MPI_C)

add_test(NAME MPIStubSanityCheck COMMAND test_mpi_stub)