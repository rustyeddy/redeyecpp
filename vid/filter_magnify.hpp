#pragma once

#include "filter.hpp"

class FltResize : public Filter
{
public:
    FltResize() : Filter("magnify") {}
    Mat& filter(Mat& iframe);
};
