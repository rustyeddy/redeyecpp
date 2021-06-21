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

    Filter*             _filter = NULL;
    Imgsrc*             _imgsrc;

public:
    Player( string name );

    void        add_imgsrc(Imgsrc *i) { _imgsrc = i; }
    void        add_filter(Filter* f) { _filter = f; }
    Filter*     get_filter(string name);

    void play( );
    void display( Mat& frame, Filter *filter = NULL );

    string to_string() { return _name; }
};

extern void mouse_callback( int event, int x, int y, int flags, void *param );

