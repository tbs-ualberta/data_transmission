cmake_minimum_required(VERSION 3.0.2)
project(data_transmission VERSION 0.2.0)
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

add_subdirectory(lib)
install(PROGRAMS install.sh
        DESTINATION bin)
