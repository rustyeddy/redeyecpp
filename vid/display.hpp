#pragma once

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Display
{
private:
    string              _name;
    std::list<string>   _filters;

public:
    Display(string name);
    void add_filter(string name);
    void display(Mat& frame);
    void display(Mat& frame, string filter);

    Mat& canny(Mat& iframe);
    Mat& gaussian(Mat& iframe);
    Mat& pyramid_down(Mat& iframe);
    bool save_avi(string fname, Mat& iframe);
};
