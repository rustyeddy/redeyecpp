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
    cv::Mat&    get_frame();        // add the << operator for reading frames

    double      get_fps()    { return _cap.get( cv::CAP_PROP_FRAME_COUNT ); }
    int         get_width()  { return _cap.get( cv::CAP_PROP_FRAME_WIDTH ); }
    int         get_height() { return _cap.get( cv::CAP_PROP_FRAME_HEIGHT ); }
};
