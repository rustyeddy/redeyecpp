#include <list>

#include <opencv2/opencv.hpp>

#include "filter.hpp"

list<string> Filters;

cv::Mat& Filter::filter(cv::Mat& iframe)
{
    return iframe;
}

FltGaussianBlur::FltGaussianBlur() : Filter("gaussian")
{
}

cv::Mat& FltGaussianBlur::filter(cv::Mat& iframe)
{
    cv::GaussianBlur( iframe, iframe, cv::Size(5,5), 3, 3);
    cv::GaussianBlur( iframe, iframe, cv::Size(5,5), 3, 3);
    return iframe;
}

cv::Mat& FltSmaller::filter(cv::Mat& iframe)
{
    cv::pyrDown( iframe, iframe );
    return iframe;
}

cv::Mat& FltCanny::filter(cv::Mat& iframe)
{
    cv::cvtColor(iframe, iframe, cv::COLOR_BGR2GRAY);
    cv::Canny( iframe, iframe, 10, 100, 3, true );
    return iframe;
}

// bool Filter::save_avi(string fname, cv::Mat& iframe)
// {
//     cv::VideoWriter wr;
//     //wr.open(fname, cv::FOURCC('M','J','P','G'), fps, size);
//     return true;
// }

