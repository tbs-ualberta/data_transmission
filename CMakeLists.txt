cmake_minimum_required(VERSION 2.8.3)

project(data_transmission)
add_compile_options(-std=c++11)

#Instructions to make the static lib
ADD_LIBRARY( data_transmission STATIC
             data_transmission.cpp )

#Instructions to install the static lib
install(TARGETS data_transmission DESTINATION /usr/local/lib/data_transmission/v0.1.0)
install(FILES data_transmission.h DESTINATION /usr/local/include/data_transmission/v0.1.0)
