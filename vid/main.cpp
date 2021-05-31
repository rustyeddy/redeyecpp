#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>

#include "vid.hpp"
#include "display.hpp"

using namespace std;

int main(int argc, char** argv )
{
    Video       *vid;
    Display     *dis;

    if ( argc < 1 )  {
        cerr << "usage: <videopath> [<filter>] <<" << endl;
        return -1;
    }

    dis = new Display( argv[0] );
    vid = new Video( argv[1] );

    int filterc = argc - 2;
    for (;;) {
        cv::Mat iframe = vid->get_frame();
        if (iframe.empty()) break;

        dis->display(iframe);   /* display with out a filter */

        for (int i = 2; i < argc; i++) {
            dis->display(iframe, argv[i]); /* display with all the filters */
        }

        // TODO process input keystrokes here
        if ( 27 == (char) cv::waitKey(33) ) break;
    }
    cout << "Goodbye, all done. " << endl;
}
