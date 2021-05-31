cmake_minimum_required(VERSION 2.8)
project( vid )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( vid
                config.cpp
                display.cpp
                filter.cpp
                main.cpp
                vid.cpp
                )       

target_link_libraries( vid ${OpenCV_LIBS} )
