cmake_minimum_required(VERSION 3.0.0)
project(archiver VERSION 0.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(compress compress/compress.c functions.c)

add_executable(decompress decompress/decompress.c functions.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
