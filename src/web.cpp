#include <string>
#include <opencv2/opencv.hpp>

#include "../include/httplib.h"
#include "../include/mjpeg_streamer.hpp"
#include "../include/nlohmann/json.hpp"

#include "filters/filters.hpp"

#include "camera.hpp"
#include "config.hpp"
#include "player.hpp"
#include "net.hpp"
#include "web.hpp"

using namespace std;

//
// This is here for https / ssl support
//
// #define CPPHTTPLIB_OPENSSL_SUPPORT
// #include "path/to/httplib.h"
// httplib::SSLServer svr;
//
const int MAX_CLIENTS = 5;
using json = nlohmann::json;

// Normal old HTTP
httplib::Server         svr;

void get_health_cb(const httplib::Request &, httplib::Response &res)
{
    json j;
    j["health"] = string("OK");
    res.set_content( j.dump(), "application/json" );
}

void get_filters_cb(const httplib::Request &, httplib::Response &res)
{
    json j;
    j["filters"] = filter_json(),
    res.set_content( j.dump(), "application/json" );
}

void get_cameras_cb(const httplib::Request &, httplib::Response &res)
{
    json j;
    j = cameras.to_json();
    res.set_content( j.dump(), "application/json" );
}

void put_camera_play_cb(const httplib::Request &, httplib::Response &res)
{
    // TODO Create an event to play camera
    json j;
    res.set_content( j.dump(), "application/json" );
}


void *web_start(void *p)
{
    svr.Get("/api/health",      get_health_cb);
    svr.Get("/api/filters",     get_filters_cb);
    svr.Get("/api/cameras",     get_cameras_cb);

    // svr.Put("/api/camera/play", put_camera_play_cb);

    // Set the Access-Control header to avoid CORS block on browser
    svr.Options(R"(\*)", [](const auto& req, auto& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
    });

    auto ret = svr.set_mount_point("/", "../www");
    if (!ret) {
        cerr << "Base directory does not exist .. " << endl;
        return NULL;
    }
    
    svr.listen("0.0.0.0", 8080);
    return NULL;
}
