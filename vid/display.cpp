#include <list>
#include <opencv2/opencv.hpp>
#include "filter.hpp"
#include "display.hpp"

using namespace cv;
using namespace std;

Display::Display(string name)
{
    _name = name;
    namedWindow(_name);
}

Filter* Display::get_filter(string name)
{
    Filter *f = NULL;
    if (name == "gaussian") {
        f = new FltGaussianBlur();
    } else if (name == "canny") {
        f = new FltCanny();
    } else if (name == "smaller") {
        f = new FltSmaller();
    }
    if (f != NULL) {
        namedWindow(name, 1);
    }
    return f;
}

void Display::display(cv::Mat& iframe)
{
    cv::imshow(_name, iframe);
}

void Display::display(Mat& iframe, string fname)
{
    Filter *filter = get_filter(fname);
    Mat &oframe = filter->filter(iframe);

    // TODO: add to a list (or map) of open windows
    imshow(fname, oframe);
}
