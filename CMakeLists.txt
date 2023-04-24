cmake_minimum_required(VERSION 3.1...3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
    trajectory
    VERSION 0.0
    LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SRC_FILES 
    src/trajectory.cpp
)

set(HEADER_FILES 
    include/trajectory.hpp
)

add_library(${PROJECT_NAME}_lib ${SRC_FILES} ${HEADER_FILES})

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)