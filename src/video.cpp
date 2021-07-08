#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>
#include "../vendors/cpp-mjpeg-streamer/single_include/nadjieb/mjpeg_streamer.hpp"

#include "config.hpp"
#include "video.hpp"

using MJPEGStreamer = nadjieb::MJPEGStreamer;
using namespace cv;
using namespace std;

std::string get_tegra_pipeline1(int width, int height, int fps) {
    return "nvarguscamerasrc sensor_id=1 ! video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080, format=(string)NV12, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

Video::Video( string camstr )
{
    cout << "Opening camstr " << camstr << endl;
    _name = camstr;

    if ( camstr == "tegra" ) {
	int capture_width = 1280 ;
	int capture_height = 720 ;
	int display_width = 1280 ;
	int display_height = 720 ;
	int framerate = 60 ;
	int flip_method = 0 ;

	std::string pipeline = gstreamer_pipeline(capture_width,
						  capture_height,
						  display_width,
						  display_height,
						  framerate,
						  flip_method);

	std::cout << "Using pipeline: \n\t";
	std::cout << "--------------------------------" << std::endl;
	std::cout << pipeline << std::endl;
	std::cout << "--------------------------------" << std::endl;

	// string t = get_tegra(1024, 768, 60);
	// cout << "TEGRA String: " << t << endl;
	_cap.open( pipeline, cv::CAP_GSTREAMER );
    } else {
	_cap.open( camstr );
    }

    cout << "Camera is NOW opened" << endl;

    if ( !_cap.isOpened() ) {
        cerr << "ERROR - the camera is not open. exiting ... " << endl;
        exit(-3);
    }

    std::vector<int> params = { cv::IMWRITE_JPEG_QUALITY, 90 };
    MJPEGStreamer streamer;
    streamer.start( config->get_mjpg_port() );

    cout << "Start collecting frames" << endl;
    bool running = true;
    while (running) {
	cv::Mat img;
	if (!_cap.read(img)) {
	    cerr << "ERROR - reading cap frame" << endl;
	    running = false;
	}
	imshow( "img", img );
	std::vector<uchar> buff_bgr;
        cv::imencode(".jpg", img, buff_bgr, params);
        streamer.publish("/video0", std::string(buff_bgr.begin(), buff_bgr.end()));
    }
}

cv::Mat& Video::get_frame()
{
    cout << "New GET FRAME a new iframe " << endl;
    if ( !_cap.isOpened() ) {
        cerr << "ERROR - the camera is not open. exiting ... " << endl;
        exit(-3);
    }

    cout << "Read a new iframe " << endl;
    if (!_cap.read(_iframe)) {
	cerr << "ERROR - reading cap frame" << endl;
	return _iframe;
    }
    cout << "Return from iframe " << endl;
    return _iframe;
}

