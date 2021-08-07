#include <string>
#include <string_view>
#include <opencv2/opencv.hpp>

// #include "../include/httplib.h"

#include <uWebSockets/App.h>
using string_view    = basic_string_view<char>;

#include "../include/mjpeg_streamer.hpp"
#include "../include/nlohmann/json.hpp"

#include "filters/filters.hpp"

#include "config.hpp"
#include "net.hpp"
#include "web.hpp"

using namespace std;

using json = nlohmann::json;

void *web_start( void * )
{
    /* HTTP */
    uWS::App().get("/*", [&asyncFileStreamer](auto *res, auto *req) {
        serveFile(res, req);
        asyncFileStreamer.streamFile(res, req->getUrl());
    }).listen(port, [port, root](auto *token) {
        if (token) {
            std::cout << "Serving " << root << " over HTTP a " << port << std::endl;
        }
    }).run();
}

#ifdef NOMAS

// Normal old HTTP
httplib::Server         svr;

void get_cameras_cb(const httplib::Request &, httplib::Response &res)
{
    // TODO - Fix this.
    json j;

    j["cameras"] = get_ip_address(config->get_iface());
    res.set_content( j.dump(), "application/json" );
}

void get_health_cb(const httplib::Request &, httplib::Response &res)
{
    res.set_content("{ \"health\": \"ok\" }", "text/plain");
}

void get_filters_cb(const httplib::Request &, httplib::Response &res)
{
    string str = filters->to_json();
    res.set_content(str, "text/pain");
}


void *web_start(void *p)
{
    svr.Get("/api/health",      get_health_cb);
    svr.Get("/api/cameras",     get_cameras_cb);
    svr.Get("/api/filters",     get_filters_cb);

    auto ret = svr.set_mount_point("/", "../www");
    if (!ret) {
        cerr << "Base directory does not exist .. " << endl;
        return NULL;
    }
    
    svr.listen("0.0.0.0", 8765);
    return NULL;
}
#endif
