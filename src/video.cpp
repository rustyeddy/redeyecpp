#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>
#include "../vendors/cpp-mjpeg-streamer/single_include/nadjieb/mjpeg_streamer.hpp"

#include "config.hpp"
#include "camera.hpp"

using MJPEGStreamer = nadjieb::MJPEGStreamer;
using namespace cv;
using namespace std;

std::string get_tegra_pipeline1(int width, int height, int fps) {
    return "nvarguscamerasrc sensor_id=0 ! video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080, format=(string)NV12, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}


