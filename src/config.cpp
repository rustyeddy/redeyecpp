#include <unistd.h>

#include "config.hpp"
#include "filters/filter.hpp"
#include "filters/filters.hpp"
#include "video.hpp"

Config::Config( int argc, char *argv[], char *envp[ ] )
{
    parse_args( argc, argv, envp );
}

int Config::parse_args( int argc, char *argv[], char *envp[] )
{
    int opt;
    while ((opt = getopt(argc, argv, "b:c:f:i:l")) != -1) {
        switch (opt) {
        case 'b':
            _mqtt_broker = optarg;
            break;

        case 'c':
            _camera_name = optarg;
            break;

            Debug = true;
            break;

        case 'f':
            _filter_name = optarg;
            break;

        case 'i':
            _iface = optarg;
            break;

        case 'l':
            _list_cameras = true;
            break;

        default:
            cerr << "ERROR unknown option: " << to_string(opt) << endl;
            cerr << "Usage: re [ -c <camera-id> | -i interface ] [-f <filter-name>] [ -b broker ]" << endl;
            exit(1);
            break;
        }
    }

    return 1;
}

#ifdef NOTNOW
Video*  Config::get_video()
{
    if ( _video_name == "" ) return NULL;
    Video *vid = new Video( _video_name );
    return vid;
}
#endif

Image*  Config::get_image()
{
    if ( _file_name  == "" ) {
        cerr << "Must specify an image to display. " << endl;
        exit(-5);
    }
    Image *img = new Image( _file_name );
    return img;
}

