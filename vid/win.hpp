#pragma once

#include <string>

using namespace std;

class Window
{
    string _name = "";
    bool _slider = false;
    int  _slider_pos = -1;

public:
    Window(string name);

    string get_name()   { return _name; }
    int get_frames() { return (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT); }
    int get_width()  { return (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH); }
    int get_height() { return (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT); }
};

