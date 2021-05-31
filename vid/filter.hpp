#pragma once

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Filter
{
private:
    string      _name;

public:
    Filter(string n)    { _name = n; }
    virtual Mat& filter(Mat& iframe);
};

class FltSmaller : public Filter {
public:
    FltSmaller() : Filter("smaller") {}
    Mat& filter(Mat& iframe);
};
    
class FltGaussianBlur : public Filter
{
public:
    FltGaussianBlur();
    Mat& filter(Mat& iframe);
}; 
    
class FltCanny : public Filter
{
public:
    FltCanny() : Filter("canny") {}
    Mat& filter(Mat& iframe);
};

// Mat& filter(Mat& ifr)
// Mat& canny(Mat& iframe);
// Mat& gaussian(Mat& iframe);
// Mat& pyramid_down(Mat& iframe);
// bool save_avi(string fname, Mat& iframe);

