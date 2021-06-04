#pragma once

#include <map>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Filter
{
protected:
    string      _name;

public:
    Filter(string n);

    string Name();       
    virtual Mat& filter(Mat& iframe) = 0;
    string to_string() { return _name; }
};
