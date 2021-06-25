#include "web.hpp"

#include "../vendors/cpp-httplib/httplib.h"

//#define CPPHTTPLIB_OPENSSL_SUPPORT
// #include "path/to/httplib.h"

// HTTP
httplib::Server svr;

// HTTPS
// httplib::SSLServer svr;
void *web_start(void *p)
{
    svr.Get("/api/health", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("{ \"health\": \"ok\" }", "text/plain");
    });

    svr.listen("0.0.0.0", 8080);
    return NULL;
}
