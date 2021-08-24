#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

#include "filter.hpp"
#include "filter_default.hpp"
#include "filter_bigger.hpp"
#include "filter_contour.hpp"
#include "filter_face_detect.hpp"
#include "filter_magnify.hpp"

#include "filters.hpp"

using namespace std;

list<string> filter_names()
{
    list<string> _filter_names;
    _filter_names.push_back("border");
    _filter_names.push_back("bigger");
    _filter_names.push_back("contour");
    _filter_names.push_back("canny");
    _filter_names.push_back("face-detect");
    _filter_names.push_back("gaussian");
    _filter_names.push_back("smaller");    
    _filter_names.push_back("resize");
    return _filter_names;
}

Filter* filter(string name)
{
    if ( name  == "border" ) {
        return new FltBorder();
    }

    if ( name == "bigger" ) {
        return new FltBigger();
    }

    if ( name == "canny" ) {
        return new FltCanny();
    }

    if ( name == "contour" ) {
        return new FltContour();
    }

    if (name == "face-detect") {
        return new FltGaussianBlur();
    }

    if (name == "smaller") {
        return new FltSmaller();
    }

    if (name == "resize") {
        return new FltResize();
    }

    // Could not find the filter !!!
    return NULL;
}

json filter_json()
{
    json j;
    auto names = filter_names();
    cout << "Filters len: " << names.size() << endl;
    std::list<std::string>::iterator it;
    for (it = names.begin(); it != names.end(); ++it) {
        j += *it;
    }
    cout << "FIL: " << j.dump() << endl;
    return j;
}

