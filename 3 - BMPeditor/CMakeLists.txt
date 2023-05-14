cmake_minimum_required(VERSION 3.0.0)
project(BMPeditor VERSION 0.1.0)

add_executable(BMPeditor main.c bmp.h get.c get.h bmpReadWrite.c bmpReadWrite.h bmpEdit.c bmpEdit.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
