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

    list<string>        _cmdlist;
    VideoWriter*        _video_writer;

    bool                _recording = false;
    bool                _paused = false;

public:
    Player( string name );

    void        add_imgsrc( Imgsrc* i ) { _imgsrc = i; }
    void        set_filter( string name );

    string      snapshot_filename()  { return "redeye-snapshot.png"; }
    string      video_filename()        { return "redeye-video.mp4"; }

    VideoWriter* get_video_writer();

    void        play();
    void        pause();

    void        record();
    void        stop();
    void        display( Mat& frame, Filter *filter = NULL );

    void        command_request(string s);
    void	check_commands();

    int         save_image( Mat& frame );

    string      to_string() { return _name; }
};

extern Player* player;
extern void* play_video( void *p ); // callback for pthreads
extern void mouse_callback( int event, int x, int y, int flags, void *param );

