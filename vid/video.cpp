#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>

#include "video.hpp"

using namespace std;

cv::Mat iframe;

Video::Video( string camstr )
{
    cout << "Opening camstr " << camstr << endl;
    _name = camstr;

    if ( camstr == "tegra" ) {
	_cap.open( get_tegra(1024,768,30), cv::CAP_GSTREAMER );
    } else {
	_cap.open( camstr );
    }
    if ( !_cap.isOpened() ) {
        cerr << "ERROR - the camera is not open. exiting ... " << endl;
        exit(-3);
    }
}

cv::Mat& Video::get_frame()
{
    if ( !_cap.isOpened() ) {
        cerr << "ERROR - the camera is not open. exiting ... " << endl;
        exit(-3);
    }
    _cap >> iframe;
    return iframe;
}

string Video::get_tegra(int width, int height, int fps)
{
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + ::to_string(width) + ", height=(int)" +
	   ::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + ::to_string(fps) +
           "/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

