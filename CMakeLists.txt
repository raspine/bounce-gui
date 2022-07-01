cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME mini-gui)
project(${PROJECT_NAME} VERSION 0.1.0)

add_subdirectory(test)
add_subdirectory(src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
