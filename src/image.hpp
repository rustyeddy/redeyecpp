#pragma once

#include <string>
#include <opencv2/opencv.hpp>

#include "imgsrc.hpp"

struct Dimensions {
    int capture_width = 1280 ;
    int capture_height = 720 ;
    int display_width = 1280 ;
    int display_height = 720 ;
    int framerate = 60 ;
    int flip_method = 0 ;

    Dimensions( int w, int h ) {
        display_width = capture_width = w;
        display_height = capture_height = h;
    }

    Dimensions( int w = 1280, int h = 720, int f = 60 ) {
        display_width = capture_width = w;
        display_height = capture_height = h;
        framerate = f;
    }
};

class Image : public Imgsrc
{
private:
    std::string _file_name = "";

public:
    Image(std::string fname);
    cv::Mat* get_frame();
};

