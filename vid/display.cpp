#include <opencv2/opencv.hpp>
#include "display.hpp"

using namespace cv;
using namespace std;

Display::Display(string name)
{
    _name = name;
}

void Display::add_filter(string name)
{
    _filters.push_back(name);
}

void Display::display(cv::Mat& iframe)
{
    cv::imshow(_name, iframe);
}

void Display::display(Mat& iframe, string filter)
{
    if (filter == "gaussian") {
        iframe = gaussian(iframe);
    } else if (filter == "canny") {
        iframe = canny(iframe);
    } else if (filter == "smaller") {
        iframe = pyramid_down(iframe);
    } else {
        cerr << "Bad filter name: " << filter << endl; // TODO - Make this a counter
    }
    cv::imshow(filter, iframe);
}

cv::Mat& Display::gaussian(cv::Mat& iframe)
{
    cv::GaussianBlur( iframe, iframe, cv::Size(5,5), 3, 3);
    cv::GaussianBlur( iframe, iframe, cv::Size(5,5), 3, 3);
    return iframe;
}

cv::Mat& Display::pyramid_down(cv::Mat& iframe)
{
    cv::pyrDown( iframe, iframe );
    return iframe;
}

cv::Mat& Display::canny(cv::Mat& iframe)
{
    cv::cvtColor(iframe, iframe, cv::COLOR_BGR2GRAY);
    //cv::imshow("Gray", igray);

    cv::Canny( iframe, iframe, 10, 100, 3, true );
    //cv::imshow( "Corny", icanny );
    return iframe;
}

bool Display::save_avi(string fname, cv::Mat& iframe)
{
    cv::VideoWriter wr;
    //wr.open(fname, cv::FOURCC('M','J','P','G'), fps, size);
    return true;
}
