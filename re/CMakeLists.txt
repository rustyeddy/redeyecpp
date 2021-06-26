cmake_minimum_required(VERSION 3.10)

project( re )

add_subdirectory( filters )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( re
                config.cpp
                cmd.cpp
                image.cpp
                main.cpp
                mqtt.cpp
                mjpg.cpp
                net.cpp
                player.cpp
                video.cpp
                web.cpp
                )       

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb -ffunction-sections")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -ffunction-sections")
set(CMAKE_BUILD_TYPE Debug)
                     
target_link_libraries( re ${OpenCV_LIBS} -lmosquitto -lpthread Filters )
