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
    string _filter_name         = "";

    string _video_name          = "";
    string _file_name           = "";
    string _gstreamer           = "";
    string _mqtt_broker         = "";
    string _iface               = "eth0";

public:
    Config( int argc, char *argv[], char *envp[] );
    int parse_args( int argc, char *argv[], char *envp[] );

    string      get_filter_name() { return _filter_name; }
    Video*      get_video();
    Image*      get_image();

    string      get_mqtt_broker();
};

extern Config *config;
