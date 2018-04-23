cmake_minimum_required(VERSION 2.8 )

project(lab2)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set( NAME_SRC
    src/lab2.cpp 
    src/Calibration.cpp
    src/Datasets.cpp
)

set( NAME_HEADERS       
    src/Calibration.h
    src/Datasets.h
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)

add_executable( lab2 ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries(lab2  ${OpenCV_LIBS})

