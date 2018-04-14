cmake_minimum_required(VERSION 3.0.2)

add_compile_options(-std=c++11)
set(VER_LIB 0.2.0)

#set (PROJECT_SOURCE_DECLARATION_DIRECTORY ${PROJECT_SOURCE_DIR}/include)
#set (MAIN_FILE ${PROJECT_SOURCE_DEFINITION_DIRECTORY}/main.cc)
set (PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

#Instructions to make the static lib
ADD_LIBRARY( data_transmission STATIC
             data_transmission.cpp )

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    ADD_LIBRARY( boostudp STATIC
            boostudp.cpp )
    target_link_libraries(boostudp ${Boost_LIBRARIES})
endif()


#Instructions to install the static lib
#install(TARGETS data_transmission
#        DESTINATION /usr/local/lib/data_transmission/v${VER_LIB})

#install(FILES data_transmission.h
#    DESTINATION /usr/local/include/data_transmission/v${VER_LIB})
install(TARGETS data_transmission boostudp
        DESTINATION lib/data_transmission/v${VER_LIB})
install(FILES data_transmission.h boostudp.h
        DESTINATION include/data_transmission/v${VER_LIB})

