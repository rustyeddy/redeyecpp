#include <list>
#include <opencv2/opencv.hpp>
#include "filter.hpp"
#include "display.hpp"
#include "externs.hpp"

using namespace cv;
using namespace std;

void mouse_callback( int event, int x, int y, int flags, void *param )
{
    Filter *f = NULL;
    if (param != NULL) {
        f = (Filter *) param;        
        cout << "Mouse Event: " << f->to_string() << " ~ event: " << event << ", x: " << x << ", y: " << y << endl;
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

Display::Display(string name)
{
    _name = name;
    namedWindow( name );
    cv::setMouseCallback( name, mouse_callback, (void *) NULL );
}

void Display::display(Mat& img, string fname)
{
    Mat &oframe = img;
    if (fname != "")  {
        Filter *filter = filters->get(fname);
        if (filter) {
            oframe = filter->filter(img);                            
        }
    } else {
        fname = main_window;
    }
    imshow(fname, oframe);
}
