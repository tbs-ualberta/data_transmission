cmake_minimum_required(VERSION 3.0.2)

project(measure_delay)
add_compile_options(-std=c++11)

set(VER_LIB 0.1.0)

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
