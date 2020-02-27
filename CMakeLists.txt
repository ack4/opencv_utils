cmake_minimum_required(VERSION 3.14)
project(opencv_utils)
set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        main.cpp
        cvutils.cpp
        )
set(HEADERS
        main.h
        cvutils.h
        )

add_executable(opencv_utils
        ${SOURCES}
        ${HEADERS}
        )

# For OpenCV
set(ENV{OpenCV_DIR} "/opencv/build")
find_package(OpenCV REQUIRED)
target_include_directories(opencv_utils PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv_utils ${OpenCV_LIBS})