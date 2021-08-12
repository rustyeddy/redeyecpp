#pragma once

#include <map>
#include <string>

#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

enum CameraState
{
    CAMERA_NOT_CONNECTED        = 13,
    CAMERA_PAUSED               = 14,
    CAMERA_PLAYING              = 15,
    CAMERA_ERROR                = 16,
};

class Camera
{
private:
    string      _id;
    string      _name;
    string      _ipaddr;
    int         _port;
    string      _macaddr;
    string      _url;

    CameraState _state  = CAMERA_NOT_CONNECTED;

    void        _init();        // initialize ipaddr/macaddr

public:
    Camera(string id);
    Camera(string id, string name);

    string id()         { return _id; }

    void play();
    void pause();               // stop streaming video
    void snapshot();            // record frame subsequent to calling this function
    void record();              // begin saving the video stream to filesystem
    void stop();                // stop saving the video stream to filesystem

    string to_string();         // spits out the url
    json   to_json();           // spits out lots of stuff including url
};

class Cameras
{
private:
    map<string,Camera*> _camera_map;

public:
    void add(string name, Camera* cam);
    json to_json();
};


