cmake_minimum_required(VERSION 3.0.0)
project(Akinator VERSION 0.1.0)

add_executable(Akinator main.c funcs.c funcs.h get.c get.h struct.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
