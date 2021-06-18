#include <iostream>

#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "player.hpp"
#include "filters/filter.hpp"
#include "video.hpp"

using namespace std;

int main(int argc, char* argv[], char *envp[] )
{
    Config *config = new Config( argc, argv, envp );

    Player*     player  = new Player( config->get_name() );
    Filter*     filter  = config->get_filter();
    Imgsrc*     imgsrc  = config->get_video();
    if ( imgsrc == NULL ) {
        imgsrc = config->get_image();
    }
    assert(imgsrc);

    cv::startWindowThread();

    player->play( imgsrc, filter );

    cv::destroyAllWindows();
    cout << "Goodbye, all done. " << endl;
}
