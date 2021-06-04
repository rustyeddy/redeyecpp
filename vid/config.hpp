#pragma once

#include <string>

#include "filter.hpp"
#include "filters.hpp"
#include "video.hpp"

using namespace std;

class Config
{
private:
    string _filter_name;
    string _vidsrc;

    FltFilters* _filters = NULL;
    Filter*     _filter = NULL;

public:
    Config( int argc, char *argv[], char *envp[] );
    int parse_args( int argc, char *argv[], char *envp[] );

    string      get_name() { return _filter_name; }

    Filter*     get_filter();
    Video*      get_video();
};
