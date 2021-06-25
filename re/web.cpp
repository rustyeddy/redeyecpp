#include <string>

#include "web.hpp"

#include "../vendors/cpp-httplib/httplib.h"

using namespace std;

//
// This is here for https / ssl support
//
// #define CPPHTTPLIB_OPENSSL_SUPPORT
// #include "path/to/httplib.h"
// httplib::SSLServer svr;
//

// Normal old HTTP
httplib::Server svr;

void mjpeg_cb(const httplib::Request &, httplib::Response &res)
{
    res.set_header("Connection", "close");
    res.set_header("Max-Age", "0");
    res.set_header("Expires", "0");
    res.set_header("Cache-Control", "no-cache, private");
    res.set_header("Pragma", "no-cache");
    res.set_header("Content-Type", "multipart/x-mixed-replace;boundary=--boundary");

#ifdef ntonotw
    bool running = true;
    while (running) {

        // TODO read mjpeg queue for a new frame

        // TODO read image from a queue ... 
        // int size = iframe.size(); //30000;       // image.size() or similar
        int size = 3000;

        string content("\r\n--JPEG-START\r\n");
        content +
            "Content-Type:image/jpeg\r\n" +
            "Content-Len:" + to_string(size) + "\r\n"
            "\r\n";

        // res.set_content( content, "image/jpeg" ); // XXX this will fail!
        // int rc = write( res.socket, content.c_str(), content.length() )


        res.set_content( "--JPEG-START", "" );        
        res.set_header("Content-Type", "image/jpeg");
        res.set_header("Content-Len", size);
        res.set_header("X-Timestamp", "0.000000");
    }
#endif // notnow

}

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
    svr.Get("/mjpeg/video0", mjpeg_cb);

    svr.listen("0.0.0.0", 8080);
    return NULL;
}
