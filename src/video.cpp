#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>

#include "video.hpp"

using namespace std;

cv::Mat iframe;

std::string get_tegra_pipeline(int width, int height, int fps) {
    return "nvarguscamerasrc sensor_id=1 ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + ", height=(int)" +
           std::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(fps) +
           "/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

Video::Video( string camstr )
{
    cout << "Opening camstr " << camstr << endl;
    _name = camstr;

    if ( camstr == "tegra" ) {
	string t = get_tegra(1024, 768, 60);
	cout << "TEGRA String: " << t << endl;
	_cap.open( t, cv::CAP_GSTREAMER );
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

// get_tegra()
string Video::get_tegra(int width, int height, int fps)
{
	return get_tegra_pipeline(width, height, fps);
    string tstr;
    
//    tstr = "nvarguscamerasrc sensor_id=0 ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)768, format=(string)NV12, framerate=(fraction)60/1 ! nvvidconv flip-method=0 ! video/x-raw, width=(int)1280, height=(int)768 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";

    cout << "TEGRA: " << tstr << endl;
    return tstr;
}

