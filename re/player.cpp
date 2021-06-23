#include <list>
#include <opencv2/opencv.hpp>
#include "externs.hpp"
#include "filters/filter.hpp"
#include "mqtt.hpp"
#include "player.hpp"


using namespace cv;
using namespace std;

extern cv::Mat iframe;          // XXX declare properly
extern cv::Mat nframe;

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

void Player::play( )
{
    // TODO - Add message channel allowing external people or programs
    // can communicate with our player
    for (;;) {

        // XXX - Lock iframe it is global 
        iframe = _imgsrc->get_frame();
        if ( iframe.empty() ) {
            cout << "Iframe empty - stopping video..." << endl;
            break;
        }
        display( iframe, _filter );            
    }
}

void Player::display(Mat& img, Filter *filter)
{
    if (filter) {
        img = filter->filter(img);
    }
    imshow( _name, img );
}

void *play_video( void *p )
{
    Player *player = (Player *) p;
    player->play( );
    return p;
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

