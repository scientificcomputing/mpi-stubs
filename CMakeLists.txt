cmake_minimum_required(VERSION 3.5.0...4.1.0)
project(mpi-abi-stubs VERSION 5.0 LANGUAGES C)

option(BUILD_SHARED_LIBS "Build libraries as SHARED" TRUE)

add_library(mpi_abi mpi.c)
set_target_properties(mpi_abi PROPERTIES VERSION 0)
set_target_properties(mpi_abi PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)

include(GNUInstallDirs)
install(FILES mpi.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS mpi_abi DESTINATION ${CMAKE_INSTALL_LIBDIR})
