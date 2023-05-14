cmake_minimum_required(VERSION 3.0.0)
project(Listing VERSION 0.1.0)

add_executable(Listing main.c header.h get.c get.h tasks.c tasks.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
