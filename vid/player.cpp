#include <list>
#include <opencv2/opencv.hpp>
#include "filter.hpp"
#include "player.hpp"
#include "externs.hpp"

using namespace cv;
using namespace std;

extern cv::Mat iframe;          // XXX declare properly

Player::Player(string name)
{
    _name = name;
    _windows.push_front(name);

    cout << "Creating named window. " << endl;

    namedWindow( name );
    moveWindow( name, _xpos, _ypos );
    _xpos += 100;
    _ypos += 100;
}

void Player::play(Video *vid, Filter *filter)
{
    for (;;) {

        // XXX - Lock iframe it is global 
        iframe = vid->get_frame();
        if ( iframe.empty()) {
            cout << "Iframe empty - stopping video..." << endl;
            break;
        }

        display( iframe, filter );

        char ch = cv::waitKey(10);
        if (ch != -1) {
            cout << "We got key char " << ::to_string(ch) << endl;            
        }
    }
}

void Player::display(Mat& img, Filter *filter)
{
    Mat &oframe = img;
    if (filter) {
        oframe = filter->filter(img);                            
    }
    moveWindow( filter->Name(), _xpos, _ypos );
    imshow( filter->Name(), oframe);
}

void mouse_callback( int event, int x, int y, int flags, void *param )
{
    Filter *f = NULL;
    if (param != NULL) {
        f = (Filter *) param;        
        cout << "Mouse Event ~  " << event << ", x: " << x << ", y: " << y << endl;
    }

    switch ( event ) {
    case EVENT_MOUSEMOVE: 
        //cout << "Mouse Move " << endl;
        break;

    case EVENT_LBUTTONDOWN:
        cout << "Mouse left button down. " << endl;
        break;

    case EVENT_LBUTTONUP:
        cout << "Mouse left button up. " << endl;
        break;

    case EVENT_RBUTTONDOWN:
        cout << "Mouse right button down. " << endl;
        break;

    case EVENT_RBUTTONUP:
        cout << "Mouse right button up. " << endl;
        break;

    default:
        cout << "Mouse event unknown " << event << endl;
    }

}

