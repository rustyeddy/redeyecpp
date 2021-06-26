#include <string>
#include <queue>

#include <opencv2/opencv.hpp>

//#include "../vendors/cpp-httplib/httplib.h"
#include "../vendors/cpp-mjpeg-streamer/single_include/nadjieb/mjpeg_streamer.hpp"

#include "config.hpp"
#include "mjpg.hpp"

using namespace std;
using namespace cv;
using MJPEGStreamer = nadjieb::MJPEGStreamer;

Mat* frame_q = NULL;

void mjpeg_iframe_q(cv::Mat& iframe)
{
    frame_q = &iframe;
}

void *mjpg_server( void *p )
{
    std::vector<int> params = { cv::IMWRITE_JPEG_QUALITY, 90 };
    MJPEGStreamer streamer;
    streamer.start( config->get_mjpg_port() );

    while ( streamer.isAlive() ) {

        if ( frame_q == NULL ) {
            usleep(200);
            continue;
        }
        Mat* f = frame_q;

        std::vector<uchar> buff_bgr;
        cv::imencode(".jpg", *f, buff_bgr, params);
        streamer.publish("/video0", std::string(buff_bgr.begin(), buff_bgr.end()));
    }

    return NULL;
}

#ifdef REMOVE
MJPGStreamer* mjpg_get_streamer()
{
    if ( mjpg_streamer == NULL ) {
        mjpg_streamer = new MJPGStreamer();
    }
    return mjpg_streamer;
}

void mjpg_stop_streamer()
{
    if ( mjpg_streamer != NULL ) {
        delete mjpg_streamer;
        mjpg_streamer = NULL;
    }
}



string get_content_type()
{
    string ContentType("HTTP/1.0 200 OK\r\n");
    ContentType += string("Server: en.code-bude.net example server\r\n");
    //to_string("Cache-Control: no-cache\r\n") +
    //  to_string("Cache-Control: private\r\n") +
    //  "Content-Type: multipart/x-mixed-replace;boundary=--boundary\r\n\r\n";
    return ContentType;
}

string get_boundary_string( int size )
{
    string bs;

    bs = string("--boundary\r\n") +
        string("Content-Type: image/jpeg\r\n") +
        "Content-Length: " +
        to_string( size ) +
        "\r\n\r\n";
    return bs;
}   

int write_mjpeg()
{
    string ct = get_content_type();
    res.set_content( ct );
    bool running = true;
    while ( running ) {
        if ( frame_q == NULL ) {
            usleep(200);
            continue;
        }

        Mat *img = frame_q;
        frame_q = NULL;

        // Image to Byte Array via OPENCV Method
        std::vector<uchar> buff;
        imencode(".jpg", img, buff);

        content += "--boundary\r\n"
            + "Content-Type: image/jpeg\r\n"     
            + "Content-Length: "
            + img.length() + "\r\n\n";

        string imgbuf(buff.begin(), buff.end());
        content += imgbuf;

        res.set_content( content );
    }
    return 0;
}
#endif // REMOVE
