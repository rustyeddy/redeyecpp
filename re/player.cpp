#include <list>
#include <vector>
#include <opencv2/opencv.hpp>

#include "../vendors/cpp-mjpeg-streamer/single_include/nadjieb/mjpeg_streamer.hpp"

#include "config.hpp"
#include "externs.hpp"
#include "filters/filter.hpp"
#include "mqtt.hpp"
#include "player.hpp"

using MJPEGStreamer = nadjieb::MJPEGStreamer;

using namespace cv;
using namespace std;

static FltFilters* filters = NULL;
static FltFilters* get_filters()
{
    if ( filters == NULL ) {
        filters = new FltFilters();
    }
    return filters;
}

extern void mjpeg_iframe_q(cv::Mat& iframe);
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

void Player::record()
{
    _recording = true;

    if ( _video_writer == NULL ) {
        _video_writer = get_video_writer();
    }
    assert( _video_writer );
}

void Player::stop()
{
    _recording = false;
    if ( _video_writer != NULL ) {
        delete _video_writer;
    }
}

void Player::check_commands( )
{
    
    // Check for incoming commands
    if ( _cmdlist.empty() ) {
        return;
    }

    // If there are incoming commands, handle them here
    string cmd = _cmdlist.back();
    _cmdlist.pop_back();

    if ( cmd == "snap" ) {

        // Save image to file.
        cout << "We have an iframe to save to file ... " << endl;
        save_image( iframe );

    } else if ( cmd == "pause" ) {

        cout << "We are being paused ... " << endl;
        _paused = true;

    } else if ( cmd == "play" ) {

        cout << "Play has been pushed ... " << endl;
        _paused = false;

    } else if ( cmd == "record" ) {

        cout << "We have a frame from video to save ... " << endl;
        record();

    } else if ( cmd == "stop" ) {
        cout << "We have recieved a stop command " << endl;
        stop();

    } else {

        cerr << "We have no support for: " << cmd << endl;
    }
}

void Player::play( )
{
    std::vector<int> params = { cv::IMWRITE_JPEG_QUALITY, 90 };
    MJPEGStreamer streamer;
    streamer.start( config->get_mjpg_port() );

    // TODO - Add message channel allowing external people or programs
    // can communicate with our player
    bool running = true;
    while ( running ) {

        // XXX - Lock iframe it is global 
        iframe = _imgsrc->get_frame();
        if ( iframe.empty() ) {
            cout << "Iframe empty - stopping video..." << endl;
            running = false;
            continue;
        }

        // empty the frames, but do not display them nor save them.
        if ( ! _paused ) {
            display( iframe, _filter );            
        }

        std::vector<uchar> buff_bgr;
        cv::imencode(".jpg", iframe, buff_bgr, params);
        streamer.publish("/video0", std::string(buff_bgr.begin(), buff_bgr.end()));

        continue;

        // if we are recording, write the frame to the video writer
        if ( _recording ) {
            assert( _video_writer );
            *_video_writer << iframe;            
        } else if ( _video_writer != NULL ) {
            delete _video_writer;
            _video_writer = NULL;
        }
    }

    cerr << "Video has stopped playing.. " << endl;
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

void Player::set_filter( string name )
{
    if ( _filter == NULL || name != _filter->Name() ) {
        filters = get_filters();
        assert( filters );

        cout << "Setting filter to " << name << endl;
        _filter = filters->get(name);

        if ( _filter == NULL ) {
            cerr << "filter fialed probably not known: " << name << endl;
        }
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

