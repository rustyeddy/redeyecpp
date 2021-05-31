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

void Display::display(Mat& iframe, string fname)
{
    Filter *filter = NULL;
    Mat &oframe = iframe;
    if (fname != "")  {
        filter = get_filter(fname);
        oframe = filter->filter(iframe);
    } else {
        fname = _name;
    }

    // TODO: add to a list (or map) of open windows
    imshow(fname, oframe);
}
