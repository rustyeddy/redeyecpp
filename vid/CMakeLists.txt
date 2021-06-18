cmake_minimum_required(VERSION 2.8)

project( vid )

add_subdirectory( filters )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( vid
                config.cpp
                image.cpp
                main.cpp
                player.cpp
                video.cpp
                )       

set(CMAKE_BUILD_TYPE Debug)
target_link_libraries( vid ${OpenCV_LIBS} Filters )
