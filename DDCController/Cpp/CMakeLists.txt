cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DDCUTIL REQUIRED ddcutil)

add_executable(main main.cpp tray/tray.cpp tray/tray.h)

target_include_directories(main PRIVATE ${DDCUTIL_INCLUDE_DIRS})

target_compile_options(main PRIVATE ${DDCUTIL_CFLAGS_OTHER})
target_link_libraries(main PRIVATE Qt6::Widgets ${DDCUTIL_LIBRARIES})
target_link_options(main PRIVATE ${DDCUTIL_LDFLAGS_OTHER})
