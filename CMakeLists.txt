cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DDCUTIL REQUIRED ddcutil)

add_executable(main
    main.cpp
    display_communicator/display_communicator.cpp
)

target_include_directories(main PRIVATE ${DDCUTIL_INCLUDE_DIRS})

target_link_libraries(main PRIVATE ${DDCUTIL_LIBRARIES})
