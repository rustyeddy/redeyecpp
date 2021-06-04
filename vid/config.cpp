#include "config.hpp"
#include "filter.hpp"
#include "filters.hpp"
#include "video.hpp"

Config::Config( int argc, char *argv[], char *envp[ ] )
{
    parse_args( argc, argv, envp );
}

int Config::parse_args( int argc, char *argv[], char *envp[] )
{
    if ( argc < 2 ) {
        cerr << "usage: vid <video-src> <filter>" << endl;
        return -1;
    }

    _vidsrc = argv[1];
    if ( argc > 2 ) {
        _filter_name = argv[2];
    }
    return 1;
}

Video*  Config::get_video()
{
    if ( _vidsrc == "" ) return NULL;
    return new Video( _vidsrc );
}

Filter* Config::get_filter()
{
    if ( _filter ) {
        return _filter;
    }

    if ( _filter_name == "" ) {
        return NULL;
    }

    _filters = new FltFilters();
    if ( _filters == NULL ) {
        return NULL;
    }
    
    _filter = _filters->get( _filter_name );
    return _filter;
}
