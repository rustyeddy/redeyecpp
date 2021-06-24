#include <list>
#include <vector>
#include <opencv2/opencv.hpp>
#include "externs.hpp"
#include "filters/filter.hpp"
#include "mqtt.hpp"
#include "player.hpp"


using namespace cv;
using namespace std;

extern Mat iframe;          // XXX declare properly
extern Mat nframe;

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

void Player::command_request(string s)
{
    cout << "Putting: " << s << " on command Q" << endl;
    _cmdlist.push_back(s);
}

void Player::play( )
{
    // TODO - Add message channel allowing external people or programs
    // can communicate with our player
    bool running = true;
    while ( running ) {

        // XXX - Lock iframe it is global 
        iframe = _imgsrc->get_frame();
        if ( iframe.empty() ) {
            cout << "Iframe empty - stopping video..." << endl;
            break;
        }

        display( iframe, _filter );            

        if ( _cmdlist.empty() ) {
            continue;
        }

        string cmd = _cmdlist.back();
        _cmdlist.pop_back();

#ifdef TODO
        if ( _saving_video ) {
            _video_writer = get_video_writer();
            _video_writer << iframe;
        }
#endif // TODO

        if ( cmd == "snap" ) {
            // Save image to file.
            cout << "We have an iframe to save to file ... " << endl;
            save_image( iframe );

        } else if ( cmd == "record" ) {

            cout << "We have a frame from video to save ... " << endl;
            // save_video( );

        } else {

            cerr << "We have no support for: " << cmd << endl;
        }
    }
}

VideoWriter* Player::get_video_writer()
{
    if ( _video_writer == NULL ) {
        _video_writer = new VideoWriter("redeye-video.mp4",
                                        VideoWriter::fourcc('m', 'p', '4', 'v'),
                                        30.0,
                                        Size(640, 480),
                                        true);
    }
    return _video_writer;
}

int Player::save_image( Mat& img )
{
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    int result = imwrite("redeye-image.png", img, compression_params);
    return result;
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

