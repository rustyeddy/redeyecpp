#pragma once

#include <string>
#include <map>

#include <opencv2/opencv.hpp>
#include "filters/filter.hpp"
#include "video.hpp"

using namespace std;
using namespace cv;

class Player
{
private:
    string              _name = "";
    list<string>        _windows;
    int                 _xpos = 100, _ypos = 100;

public:
    Player( string name );

    void        add_filter(string name, Filter* f);
    Filter*     get_filter(string name);

    void play( Imgsrc *imgsrc, Filter *filter = NULL );
    void display( Mat& frame, Filter *filter = NULL );

    string to_string() { return _name; }
};

extern void mouse_callback( int event, int x, int y, int flags, void *param );

