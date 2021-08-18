#include <unistd.h>
#include <string>

#include <opencv2/opencv.hpp>

#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

#include "camera.hpp"
#include "config.hpp"
#include "image.hpp"
#include "tegra.hpp"


extern string IP; 

Camera::Camera(string id)
{
    _id = id;
    _name = id;
}

Camera::Camera(string id, string name)
{
    _id = id;
}

void Camera::init()
{
    _ipaddr     = IP;
    _port       = config->get_mjpg_port();

    if ( _id == "video0" || _id == "video1 ") {
        _id = "/dev/" + _id;
    }

    Dimensions dims = Dimensions(); // go with defaults
    if ( _id == "csi0" || _id == "csi1" ) {
        std::string pipeline = gstreamer_pipeline(dims.capture_width,
						  dims.capture_height,
						  dims.display_width,
						  dims.display_height,
						  dims.framerate,
						  dims.flip_method);

	std::cout << "Gstreamer pipeline: \n\t";
	std::cout << "--------------------------------" << std::endl;
	std::cout << pipeline << std::endl;
	std::cout << "--------------------------------" << std::endl;

        _cap.open( pipeline, cv::CAP_GSTREAMER );

    } else {

        _cap.open( _id );

    }

    if ( !_cap.isOpened() ) {
        cerr << "ERROR - the camera " + _id + " failed open. exiting ... " << endl;
        return;
    }
    _initialized = true;
    cout << "Camera " + _id + " is NOW opened" << endl;
}

cv::Mat* Camera::get_frame()
{
    if ( !_cap.isOpened() ) {
        cerr << "ERROR - the camera is not open. exiting ... " << endl;
        exit(-3);
    }

    Mat* iframe = new cv::Mat();
    if (!_cap.read( *iframe )) {
	cerr << "ERROR - reading cap frame" << endl;
        exit(-3);
    }
    return iframe;
}


void Camera::play()
{
    if (! _initialized ) {
        init();
    }

    while ( 1 ) {
        Mat* f = get_frame();

        if (  f->empty() ) {
            usleep(100);
            continue;
        }
        frameQ.push(f);
    }
}

void Camera::pause()
{
    cout << "Camera paused ... " << endl;    
}

string Camera::make_url()
{
    string p = ::to_string(_port);
    string id = _id;
    return "http://" + _ipaddr + ":" + p + "/" + _name;
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
