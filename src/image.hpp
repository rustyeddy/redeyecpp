#pragma once

#include <string>
#include <opencv2/opencv.hpp>

#include "imgsrc.hpp"

class Image : public Imgsrc
{
private:
    std::string _file_name = "";

public:
    Image(std::string fname);
    cv::Mat* get_frame();
};

