cmake_minimum_required(VERSION 3.5.0...4.1.0)
project(mpi-abi-stubs VERSION 5.0 LANGUAGES C)

option(BUILD_SHARED_LIBS "Build libraries as SHARED" TRUE)

add_library(mpi mpi.c)
set_target_properties(mpi PROPERTIES VERSION 12)
set_target_properties(mpi PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)

include(GNUInstallDirs)
install(FILES mpi.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS mpi DESTINATION ${CMAKE_INSTALL_LIBDIR})
