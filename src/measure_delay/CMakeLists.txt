cmake_minimum_required(VERSION 3.0.2)

project(measure_delay)
add_compile_options(-std=c++11)
set(CMAKE_INSTALL_PREFIX /usr/local)

set(VER_LIB 0.2.0)

include_directories(
    ${CMAKE_INSTALL_PREFIX}/include/Timer
    /usr/include
    ${CMAKE_INSTALL_PREFIX}/include/data_transmission)

add_executable(measure_delay_snd src/measure_delay_snd.cpp)
add_executable(measure_delay_rcv src/measure_delay_rcv.cpp)
add_executable(measure_delay_loopback src/measure_delay_loopback.cpp)

# Third-party libraries:
#   - https://github.com/tdl-tbslab/Timer
#   - https://github.com/funcman/fCSV
target_link_libraries(
  measure_delay_snd
  ${CMAKE_INSTALL_PREFIX}/lib/libdata_transmission.a
  ${CMAKE_INSTALL_PREFIX}/lib/Timer/libTimer.a
  pthread
)
target_link_libraries(
  measure_delay_rcv
  ${CMAKE_INSTALL_PREFIX}/lib/libdata_transmission.a
  /usr/lib/libfcsv.a
)
target_link_libraries(
  measure_delay_loopback
  ${CMAKE_INSTALL_PREFIX}/lib/libdata_transmission.a
)

install(TARGETS measure_delay_snd measure_delay_rcv measure_delay_loopback
        DESTINATION bin)
