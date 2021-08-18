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

extern void mjpeg_iframe_q(cv::Mat& iframe);
extern string camera_name;

static FltFilters* get_filters()
{
    if ( filters == NULL ) {
        filters = new FltFilters();
    }
    return filters;
}

Player::Player(Camera* cam)
{
    _cam = cam;
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
        //save_image( iframe );

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

void Player::stream( cv::Mat* mat )
{
    std::vector<int> params = { cv::IMWRITE_JPEG_QUALITY, 90 };
    std::vector<uchar> buff_bgr;
    cv::imencode(".jpg", *mat, buff_bgr, params);
    _streamer.publish("/video0", std::string(buff_bgr.begin(), buff_bgr.end()));
}

void Player::play_loop( )
{
    while (1) {
        cv::Mat* iframe = _cam->get_frame();

        // move this up
        if ( _filter ) {
            iframe = _filter->filter( iframe );
        }

        stream ( iframe );
        if ( ! _paused && _local_display ) {
            display( iframe );
        }
        if ( _recording && _video_writer ) {
            // _video_writer << &iframe;
        }
	delete iframe;
    }
}

void *play_loop( void *p )
{
    cout << "PLay loop for  " << camera_name << endl;
    Camera *cam = cameras.get(camera_name);
    if (cam == NULL) {
        cout << "Unknown camera " << camera_name << endl;
        return NULL;
    }
    Player *player = new Player(cam);
    player->play();

    return NULL;
}

void Player::play( )
{
    _recording = true;
    
    // Start the streamer 
    _streamer.start( config->get_mjpg_port() );
    _streaming = true;

    // _cam->play();
    _cam->init();
    while ( _recording ) {

	cv::Mat* iframe = _cam->get_frame();
        if ( iframe == NULL || iframe->empty() ) {
            cout << "Iframe empty - stopping video..." << endl;
            _recording = false;
            continue;
        }

        int size = _frameQ.size();
        if ( size > _frameQ_max ) {
            _frameQ_max = size;
        }
        
        if ( size > 4 ) {
            _frameQ_dropped++;
            delete iframe;
            continue;
        }

        //_frameQ.push( iframe );

        if ( _filter ) {
            iframe = _filter->filter( iframe );
        }

        stream ( iframe );
        if ( ! _paused && _local_display ) {
            display( iframe );
        }
        if ( _recording && _video_writer ) {
            // _video_writer << &iframe;
        }
	delete iframe;
    }

    //pthread_join( t_playloop, NULL );

    _streamer.stop();
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
    std::vector<int> params = { cv::IMWRITE_JPEG_QUALITY, 90 };
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

void Player::display( Mat* img )
{
    imshow( _cam->id(), *img );
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

