cmake_minimum_required(VERSION 3.16)

project(bad_apple_player LANGUAGES CXX)

if(NOT MSVC)
    # Для MinGW
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED core imgcodecs highgui)

add_executable(bad_apple_player
    main.cpp
    header.hpp)

target_include_directories(bad_apple_player PRIVATE ${OPENCV_INCLUDE_DIRS})
target_link_libraries(bad_apple_player PRIVATE ${OpenCV_LIBS})
