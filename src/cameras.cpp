#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

#include "camera.hpp"
#include "config.hpp"
extern string IP; 

void Cameras::add(string name, Camera* cam)
{
    _camera_map[name] = cam;
}

Camera* Cameras::get(string name)
{
    if ( _camera_map.find(name) == _camera_map.end() ) {
        return NULL;
    }
    return _camera_map[name];
}

json Cameras::to_json()
{
    json j;

    for (std::map<string,Camera*>::iterator it = _camera_map.begin();
         it != _camera_map.end(); ++it) {
        Camera *cam = (Camera *) it->second;
        // j[it->first] = cam->to_json();
        j += cam->to_json();
    }
    return j;
}



