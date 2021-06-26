#pragma once

#include <list>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void *mjpg_server( void *p );
void mjpeg_iframe_q( Mat& frame ); 


