#include <iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

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

    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw   = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph   = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    cout << "Video is playing " << frames << " frame/sec at "
         << tmpw << "w by "
         << tmph << "h"
         << endl;

    //cv::createTrackbar()
    cv::Mat frame;
    for (;;) {
        g_cap >> frame;
        if ( frame.empty() ) break;

        cv::imshow("VID: ", frame );
        if ( (char) cv::waitKey(33) >= 0 ) break;
    }
    return 0;
}
