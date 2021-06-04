#include <opencv2/opencv.hpp>

#include "filter.hpp"
#include "filter_contour.hpp"

extern cv::Mat iframe;          // XXXXX declare properly

void contour_trackbar_cb( int, void* );
void contour_mouse_cb( int event, int x, int y, int flags, void *param );

FltContour::FltContour() : Filter("contour")
{
}

cv::Mat& FltContour::filter(cv::Mat& img)
{
    static bool init = true;
    if (init) {
        cout << "Intializing mouse callback" << endl;
        cv::setMouseCallback( _name, contour_mouse_cb, (void *) this ); 
        init = false;
    }

    cv::Mat bin;
    cv::threshold( iframe, bin, get_threshold(), 255, cv::THRESH_BINARY );
    vector< vector< cv::Point> > contours;
    cv::findContours( bin, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE );
    bin = cv::Scalar::all(0);

    cv::drawContours( bin, contours, -1, cv::Scalar::all(255));
    return img;
}

void contour_trackbar_cb( int val, void *param )
{
    FltContour *flt = (FltContour *) param;

    // flt->filter( iframe );
    
    cout << "TODO change trackbar threshold value." << endl;
}

void contour_mouse_cb( int event, int x, int y, int flags, void *param )
{
    FltContour *flt = (FltContour *) param;
    cout << "Mouse Event: " << event << ", x: " << x << ", y: " << y;

    switch ( event ) {
    case EVENT_MOUSEMOVE: 
        cout << " --- Move " << endl;
        break;

    case EVENT_LBUTTONDOWN:
        cout << " --- left button down - start box. " << endl;
        break;

    case EVENT_LBUTTONUP:
        cout << " --- left button up. " << endl;
        break;

    case EVENT_RBUTTONDOWN:
        cout << " --- right button down. " << endl;
        break;

    case EVENT_RBUTTONUP:
        cout << " --- right button up. " << endl;
        break;

    default:
        cout << " ---  unknown " << event << endl;
    }

}
