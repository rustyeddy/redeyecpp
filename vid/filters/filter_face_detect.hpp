#pragma once

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

#include "filter.hpp"

using namespace std;

// Face detector using Haar Cascade Classifier
class FltHaarCascade : public Filter {
private:
    cv::CascadeClassifier _face_cascade;
    cv::CascadeClassifier _eyes_cascade;

    void detectAndDisplay( cv::Mat frame );    

public:
    FltHaarCascade() : Filter("face-detect") {}

    cv::Mat& filter(cv::Mat& iframe);
};


