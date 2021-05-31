#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>

#include "vid.hpp"

using namespace std;


Video::Video(string camstr)
{
    cout << "Opening camstr " << camstr << endl;
    _cap.open( camstr );
}

cv::Mat Video::get_frame()
{
    cv::Mat iframe;
    _cap >> iframe;
    return iframe;
}
