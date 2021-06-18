cmake_minimum_required(VERSION 2.8)

project( filters )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_library( Filters filters
	filter.cpp
	filter_bigger.cpp
	filter_contour.cpp
	filter_default.cpp
	filter_face_detect.cpp
	filter_magnify.cpp
	filters.cpp
)

set(CMAKE_BUILD_TYPE Debug)
