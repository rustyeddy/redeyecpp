#pragma once

#include <string>
#include <map>

#include <opencv2/opencv.hpp>
#include "filter.hpp"

using namespace std;
using namespace cv;

class Display
{
private:
    string              _name = "";

protected:
    map<string,Filter*> _filters;
    Mat*                _image = NULL;

public:
    Display(string name);

    void        add_filter(string name, Filter* f);
    Filter*     get_filter(string name);

    Mat& filter(Mat& frame);
    void display(Mat& frame, string filter = "");
    string to_string() { return _name; }
};
