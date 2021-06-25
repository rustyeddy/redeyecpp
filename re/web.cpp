#include "web.hpp"

#include "../vendors/cpp-httplib/httplib.h"

//
// This is here for https / ssl support
//
// #define CPPHTTPLIB_OPENSSL_SUPPORT
// #include "path/to/httplib.h"
// httplib::SSLServer svr;
//

// Normal old HTTP
httplib::Server svr;

void get_cameras_cb(const httplib::Request &, httplib::Response &res)
{
    res.set_content( "{ \"cameras\": \"10.24.10.10\"}", "text/plain" );
}

void *web_start(void *p)
{
    svr.Get("/api/health", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("{ \"health\": \"ok\" }", "text/plain");
    });

    svr.Get("/api/cameras", get_cameras_cb);

    svr.listen("0.0.0.0", 8080);
    return NULL;
}
