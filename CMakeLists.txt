cmake_minimum_required(VERSION 4.2)
project(3part LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(3part 
	3part.cpp
	graphic_elements.cpp
)

if(MSVC)
    target_compile_options(3part PRIVATE /W4)
else()
    target_compile_options(3part PRIVATE -Wall -Wextra -Wpedantic )
endif()