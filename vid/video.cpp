#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>

#include "video.hpp"

using namespace std;

cv::Mat iframe;

Video::Video( string camstr )
{
    cout << "Opening camstr " << camstr << endl;
    _name = camstr;
    _cap.open( camstr );
    if ( !_cap.isOpened() ) {
        cerr << "ERROR - the camera is not open. exiting ... " << endl;
        exit(-3);
    }
}

cv::Mat& Video::get_frame()
{
    if ( !_cap.isOpened() ) {
        cerr << "ERROR - the camera is not open. exiting ... " << endl;
        exit(-3);
    }
    _cap >> iframe;
    return iframe;
}

