#pragma once

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Filter
{
private:
    string      _name;

protected:
    Mat*        _image = NULL;

public:
    Filter(string n) { _name = n; }
    virtual Mat& filter(Mat& iframe);
    string to_string() { return _name; }
};

class FltNULL : public Filter {
public:
    FltNULL() : Filter("") {}
    Mat& filter(Mat& iframe);
};

class FltSmaller : public Filter {
public:
    FltSmaller() : Filter("smaller") {}
    Mat& filter(Mat& iframe);
};
    
class FltGaussianBlur : public Filter
{
public:
    FltGaussianBlur() : Filter("gaussian") {}
    Mat& filter(Mat& iframe);
}; 
    
class FltCanny : public Filter
{
public:
    FltCanny() : Filter("canny") {}
    Mat& filter(Mat& iframe);
};


