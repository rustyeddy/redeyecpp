#include <string>
#include <opencv2/opencv.hpp>

#include "image.hpp"

Image::Image(std::string fname)
{
    _file_name = fname;
}

cv::Mat& Image::get_frame()
{
    //_iframe = cv::imread( _file_name, cv::IMREAD_COLOR );
    _iframe = cv::imread( _file_name, cv::IMREAD_GRAYSCALE );
    return _iframe;
}
