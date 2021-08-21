#pragma once

#include <queue>
#include <string>

using namespace std;

enum EVENT_TYPE
{
    EVENT_NONE          = 0,
    EVENT_CAMERA_PLAY   = 1,
    EVENT_CAMERA_PAUSE  = 2,
    EVENT_FILTER        = 3,
    EVENT_EXIT          = 4,
    EVENT_MAX           = 5,
};

class Event
{
private:
    EVENT_TYPE  _event_type         = EVENT_NONE;
    string      _camera;
    string      _arg;

public:
    Event( EVENT_TYPE t, string cam )       { _event_type = t; _camera = cam; }

    EVENT_TYPE  get_type()      { return _event_type; }
    string      get_camera()    { return _camera; }
    string      get_args()      { return _arg; }
};

extern queue<Event*>    eventQ;
