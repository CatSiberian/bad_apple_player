cmake_minimum_required(VERSION 3.21)
project(bad_apple_player LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

find_package(OpenCV REQUIRED core imgcodecs videoio imgproc)

add_executable(bad_apple_player main.cpp header.hpp)
target_include_directories(bad_apple_player PRIVATE ${OPENCV_INCLUDE_DIRS})
target_link_libraries(bad_apple_player PRIVATE ${OpenCV_LIBS})

#Это вспомогательный cmake-скрипт для копирования зависимостей
install(TARGETS bad_apple_player DESTINATION .)

# Этот блок выполнится после сборки
add_custom_command(TARGET bad_apple_player POST_BUILD
    COMMAND ${CMAKE_COMMAND} -D "EXECUTABLE=$<TARGET_FILE:bad_apple_player>"
            -D "SEARCH_DIRS=C:/msys64/mingw64/bin"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/copy_dlls.cmake"
    COMMENT "Resolving and copying all DLL dependencies..."
)
