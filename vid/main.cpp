#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>

#include "vid.hpp"
#include "display.hpp"

using namespace std;

// The trackbar can only be used on saved video files, live video is
// not supported.
/*
int g_run = 1;
int g_dontset = 0;

bool g_do_gausian = false;
bool g_do_pyr_down = false;
bool g_do_canny = true;
bool g_do_save_avi = true;
string fname = "";
*/

int main(int argc, char** argv )
{
    Video       *vid;
    Display     *dis;

    if ( argc < 2 )  {
        printf("usage: <videopath> [<filter>]\n");
        return -1;
    }

    vid = new Video( argv[1] );
    cout << "Video player has been created." << endl;

    dis = new Display("guassian");
    cout << "Video display has been created." << endl;

    for (;;) {
        cv::Mat iframe = vid->get_frame();
        if (iframe.empty()) break;

        dis->display(iframe);
        dis->display(iframe, argv[2]);

        if ( 27 == (char) cv::waitKey(33) ) break;
    }
    cout << "Goodbye, all done. " << endl;
}
