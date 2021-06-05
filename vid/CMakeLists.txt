cmake_minimum_required(VERSION 2.8)

project( vid )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( vid
                config.cpp
                filter.cpp
                filter_default.cpp
                filter_bigger.cpp
                filter_magnify.cpp
                filter_contour.cpp
                filters.cpp
                image.cpp
                main.cpp
                player.cpp
                video.cpp
                )       

target_link_libraries( vid ${OpenCV_LIBS} )
