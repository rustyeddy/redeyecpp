#pragma once

#include <string>

#include "filters/filter.hpp"
#include "filters/filters.hpp"
#include "image.hpp"
#include "video.hpp"

using namespace std;

class Config
{
private:
    string      _camera_name     = "";
    string      _filter_name    = "";
    string      _file_name      = "";
    string      _gstreamer      = "";
    string      _iface          = "eth0";
    bool        _list_cameras   = false;
    string      _mqtt_broker    = "10.11.10.10";
    int         _mjpg_port      = 1234;
    string      _video_uri      = "/video0";
    int         _web_port       = 80;

public:
    bool        Debug           = false;

    Config( int argc, char *argv[], char *envp[] );
    int parse_args( int argc, char *argv[], char *envp[] );

    string      get_filter_name()       { return _filter_name; }
    string      get_camera_name()       { return _camera_name; }

    string      get_mqtt_broker()       { return _mqtt_broker; }
    int         get_mjpg_port()         { return _mjpg_port; }
    string      get_video_uri()         { return _video_uri; } 
    int         get_web_port()          { return _web_port; }

    string	get_iface()		{ return _iface; }

    Video*      get_video();
    Image*      get_image();
};

extern Config *config;
