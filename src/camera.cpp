#include <string>

#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

#include "camera.hpp"
#include "config.hpp"
extern string IP; 

Camera::Camera(string id)
{
    _id = id;
    _name = id;
    _init();
}

Camera::Camera(string id, string name)
{
    _id = id;
    _init();
}

void Camera::_init()
{
    _ipaddr     = IP;
    _port       = config->get_mjpg_port();
}

string Camera::to_string()
{
    string p = ::to_string(_port);
    string id = _id;
    if (_id == "/dev/video0") {
        id = "video0";
    } else if ( _id == "/dev/video1" ) {
        id = "video1";
    }
    return "http://" + _ipaddr + ":" + p + "/" + id;
}

json Camera::to_json()
{
    json j;

    j["id"]     = _id;
    j["ipaddr"] = _ipaddr;
    j["port"]   = _port;
    j["macaddr"]= _macaddr;
    j["name"]   = _name;        
    j["url"]    = to_string();
    return j;
}

void Cameras::add(string name, Camera* cam)
{
    _camera_map[name] = cam;
}

json Cameras::to_json()
{
    json j;

    for (std::map<string,Camera*>::iterator it = _camera_map.begin(); it != _camera_map.end(); ++it) {
        Camera *cam = (Camera *) it->second;
        cout << it->first << " => " << cam->to_string() << endl;
    }
    return j;
}



