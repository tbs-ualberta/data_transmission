cmake_minimum_required(VERSION 3.0.2)

project(data_transmission VERSION 0.1.0)
add_compile_options(-std=c++11)

set(VER_LIB 0.1.0)

#Instructions to make the static lib
ADD_LIBRARY( data_transmission STATIC
             data_transmission.cpp )

#Instructions to install the static lib
install(TARGETS data_transmission
    DESTINATION /usr/local/lib/data_transmission/v${VER_LIB})
install(FILES data_transmission.h
    DESTINATION /usr/local/include/data_transmission/v${VER_LIB})

include_directories(
    /usr/local/include/Timer
    /usr/include
    /usr/local/include/data_transmission/v${VER_LIB})

add_executable(measure_delay_snd measure_delay_snd.cpp)
add_executable(measure_delay_rcv measure_delay_rcv.cpp)
add_executable(measure_delay_loopback measure_delay_loopback.cpp)

# Third-party libraries:
#   - https://github.com/tdl-tbslab/Timer
#   - https://github.com/funcman/fCSV
target_link_libraries(
  measure_delay_snd
  /usr/local/lib/data_transmission/v${VER_LIB}/libdata_transmission.a
  /usr/local/lib/Timer/libTimer.a
  pthread
)
target_link_libraries(
  measure_delay_rcv
  /usr/local/lib/data_transmission/v${VER_LIB}/libdata_transmission.a
  /usr/lib/libfcsv.a
)
target_link_libraries(
  measure_delay_loopback
  /usr/local/lib/data_transmission/v${VER_LIB}/libdata_transmission.a
)

install(TARGETS measure_delay_snd measure_delay_rcv measure_delay_loopback
        DESTINATION /usr/local/bin)
