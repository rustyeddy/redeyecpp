#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>

#include "vid.hpp"
#include "display.hpp"
#include "filter.hpp"
#include "filter_default.hpp"
#include "filters.hpp"
#include "externs.hpp"

using namespace std;

string          main_window = "Video";
FltFilters*     filters;
Display*        display;
Video*          video;

int main(int argc, char** argv )
{
    if ( argc < 2 )  {
        cerr << "usage: <videopath> [<filter>] <<" << endl;
        return -1;
    }

    display = new Display( main_window );
    video = new Video( argv[1] );
    filters = new FltFilters();
    
    cv::startWindowThread();
    for (;;) {
        cv::Mat iframe = video->get_frame();
        if (iframe.empty()) break;

        display->display(iframe);   /* display with out a filter */
        for (int i = 2; i < argc; i++) {
            display->display(iframe, argv[i]); // display with all the filters */
        }

        // TODO process input keystrokes here
        if ( 27 == (char) cv::waitKey(33) ) break;
    }

    cv::destroyAllWindows();
    cout << "Goodbye, all done. " << endl;
}
