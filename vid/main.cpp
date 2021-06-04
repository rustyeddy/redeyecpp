#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "player.hpp"
#include "filter.hpp"
#include "filter_default.hpp"
#include "filters.hpp"
#include "video.hpp"
#include "externs.hpp"

using namespace std;


int main(int argc, char* argv[], char *envp[] )
{
    Config *config = new Config( argc, argv, envp );

    Player*     player  = new Player( config->get_name() );
    Video*      video   = config->get_video();
    Filter*     filter  = config->get_filter();

    cv::startWindowThread();

    player->play( video, filter );

    cv::destroyAllWindows();

    cout << "Goodbye, all done. " << endl;
}
