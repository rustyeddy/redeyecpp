#pragma once

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;

class Video
{
    string              _name;
    cv::VideoCapture    _cap;
    
public:
    Video(string name);
    cv::Mat get_frame();
};
