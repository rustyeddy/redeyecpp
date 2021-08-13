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

string Camera::make_url()
{
    string p = ::to_string(_port);
    string id = _id;
    return "http://" + _ipaddr + ":" + p + "/" + id;
}

string Camera::to_string()
{
    return make_url();
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

void Camera::play()
{
    cout << "Camera playing ... " << endl;
}

void Camera::pause()
{
    cout << "Camera paused ... " << endl;    
}
