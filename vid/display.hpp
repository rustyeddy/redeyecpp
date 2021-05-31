#pragma once

#include <string>
#include <list>

#include <opencv2/opencv.hpp>
#include "filter.hpp"

using namespace std;
using namespace cv;

#include <string>

#include "filter.hpp"

class Display
{
private:
    string         _name;

protected:
    string      _win_main       = "vid";

public:
    Display(string name);
    Filter* get_filter(string name);
    void display(Mat& frame);
    void display(Mat& frame, string filter);
    Mat& filter(Mat& frame);
};
