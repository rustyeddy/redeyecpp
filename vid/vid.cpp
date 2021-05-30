#include <iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

// The trackbar can only be used on saved video files, live video is
// not supported.
int g_slider_position = 0;
int g_run = 1;
int g_dontset = 0;

cv::VideoCapture g_cap;

void onTrackbarSlide( int pos, void * ) {
    g_cap.set( cv::CAP_PROP_POS_FRAMES, pos );

    if ( !g_dontset ) {
        g_run = 1;
        g_dontset = 0;
    }
}


int main(int argc, char** argv )
{
    if ( argc != 2 )  {
        printf("usage: <videopath>\n");
        return -1;
    }

    cv::namedWindow( "Vid Viewer", cv::WINDOW_AUTOSIZE );
    g_cap.open(argv[1]);

    // Choose a more descriptive name
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw   = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph   = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cout << "Video is playing " << frames << " frame/sec at "
         << tmpw << "w by "
         << tmph << "h"
         << endl;

    if (frames > 0) {
        cv::createTrackbar("Position", "X", &g_slider_position, frames, onTrackbarSlide);
    }

    cv::Mat frame;
    for (;;) {

        if ( g_run ) {

            g_cap >> frame;
            if ( frame.empty() ) break;

            int curpos = (int) g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;

            cout << "CURPOS: " << curpos << endl;
            
            if (frames > 0) {
                cv::setTrackbarPos("Postion", "X", curpos);                
            }
            cv::imshow("X ", frame );
            if ( (char) cv::waitKey(33) >= 0 ) break;

            g_run = -1;
        }

        char c = (char) cv::waitKey(10);
        switch (c) {
        case 's':
            g_run = 1;
            break;

        case 'r':
            g_run = -1;

        case 27:
            break;

        default:
            //cout << "What the heck was that? " << c << endl;
            break;
        }
        if (false) { // make this a debug
            cout << "g_run: " << g_run << endl;                        
        }
    }
    return 0;
}
