#include <iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

void do_gausian(cv::Mat& iframe);
void do_pyramid_down(cv::Mat& iframe);
void do_canny(cv::Mat& iframe);

// The trackbar can only be used on saved video files, live video is
// not supported.
int g_slider_position = 0;
int g_run = 1;
int g_dontset = 0;
bool g_do_gausian = false;
bool g_do_pyr_down = false;
bool g_do_canny = true;


cv::VideoCapture g_cap;

int main(int argc, char** argv )
{
    if ( argc != 2 )  {
        printf("usage: <videopath>\n");
        return -1;
    }

    //do_main_window();
    g_cap.open(argv[1]);
    cv::Mat iframe, oframe;
    
    for (;;) {

        if ( g_run ) {

            g_cap >> iframe;
            if ( iframe.empty() ) break;

            cv::imshow("Original Image", iframe );

            if (g_do_gausian) {
                do_gausian(iframe);
            }

            if (g_do_pyr_down) {
                do_pyramid_down(iframe);
            }

            if (g_do_canny) {
                do_canny(iframe);
            }
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

void onTrackbarSlide( int pos, void * ) {
    g_cap.set( cv::CAP_PROP_POS_FRAMES, pos );

    if ( !g_dontset ) {
        g_run = 1;
        g_dontset = 0;
    }
}

void do_gausian(cv::Mat& iframe)
{
    cv::Mat oframe;
    cv::GaussianBlur( iframe, oframe, cv::Size(5,5), 3, 3);
    cv::GaussianBlur( oframe, oframe, cv::Size(5,5), 3, 3);

    cv::imshow("Y ", oframe);
}

void do_pyramid_down(cv::Mat& iframe)
{
    cv::Mat oframe;
    cv::pyrDown( iframe, oframe );
}

void do_canny(cv::Mat& iframe)
{
    cv::Mat igray, icanny;
    cv::cvtColor(iframe, igray, cv::COLOR_BGR2GRAY);
    cv::imshow("Gray", igray);

    cv::Canny( igray, icanny, 10, 100, 3, true );
    cv::imshow( "Corny", icanny );
}

void do_main_window()
{
    // Choose a more descriptive name
    //cv::namedWindow( "Vid Viewer", cv::WINDOW_AUTOSIZE );
    //cv::namedWindow( "Vid Other", cv::WINDOW_AUTOSIZE );
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
    int curpos = (int) g_cap.get(cv::CAP_PROP_POS_FRAMES);
    g_dontset = 1;
    if (curpos > 0) {
        cv::setTrackbarPos("Postion", "X", curpos);                
    }
}

