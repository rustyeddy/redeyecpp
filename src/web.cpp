#include <string>
#include <opencv2/opencv.hpp>
#include "web.hpp"

#include "../vendors/cpp-httplib/httplib.h"
#include "../vendors/cpp-mjpeg-streamer/single_include/nadjieb/mjpeg_streamer.hpp"
using namespace std;

//
// This is here for https / ssl support
//
// #define CPPHTTPLIB_OPENSSL_SUPPORT
// #include "path/to/httplib.h"
// httplib::SSLServer svr;
//
const int MAX_CLIENTS = 5;

// Normal old HTTP
httplib::Server         svr;

void get_cameras_cb(const httplib::Request &, httplib::Response &res)
{
    res.set_content( "{ \"cameras\": \"10.24.10.10\"}", "text/plain" );
}

void get_health_cb(const httplib::Request &, httplib::Response &res)
{
    res.set_content("{ \"health\": \"ok\" }", "text/plain");
}

void *web_start(void *p)
{
    svr.Get("/api/health",      get_health_cb);
    svr.Get("/api/cameras",     get_cameras_cb);
    svr.listen("0.0.0.0", 8765);
    return NULL;
}
