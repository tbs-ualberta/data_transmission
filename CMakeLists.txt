cmake_minimum_required(VERSION 3.0.2)

project(data_transmission VERSION 0.2.0)
add_compile_options(-std=c++11)

set(VER_LIB 0.2.0)

#Instructions to make the static lib
ADD_LIBRARY( data_transmission STATIC
             data_transmission.cpp )

#Instructions to install the static lib
install(FILES data_transmission.h
    DESTINATION /usr/local/include/data_transmission/v${VER_LIB})
install(TARGETS data_transmission
    DESTINATION /usr/local/lib/data_transmission/v${VER_LIB})
