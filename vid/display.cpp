#include <list>
#include <opencv2/opencv.hpp>
#include "filter.hpp"
#include "display.hpp"

using namespace cv;
using namespace std;

void mouse_callback( int event, int x, int y, int flags, void *param )
{
    Filter *f = (Filter *) param;
    if (param == NULL) {
        f = new FltNULL();
    }
    // cout << "Mouse Event: " << f->to_string() << " ~ event: " << event << ", x: " << x << ", y: " << y << endl;
    //f->mouse_callback( event, x, y, flags );

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

Display::Display(string name)
{
    _name = name;
    _image = NULL;

    namedWindow( name );
    cv::setMouseCallback( name, mouse_callback, (void *) NULL );
}

void Display::add_filter(string name, Filter* f)
{
    _filters[name] = f;
    namedWindow( name );
    cv::setMouseCallback( name, mouse_callback, (void *) f );
}

Filter* Display::get_filter(string name)
{
    Filter *f = NULL;
    auto it = _filters.find(name);
    if (it != _filters.end()) {
        f = _filters[name];
    }
    return f;
}

void Display::display(Mat& iframe, string fname)
{
    _image = &iframe;

    Filter *filter = NULL;
    Mat &oframe = iframe;

    if (fname != "")  {
        filter = get_filter(fname);
        oframe = filter->filter(iframe);
    } else {
        fname = _name;
    }

    // TODO: add to a list (or map) of open windows
    imshow(fname, oframe);
}
