#include <iostream>
#include <thread>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "mqtt.hpp"
#include "player.hpp"
#include "video.hpp"
#include "filters/filter.hpp"

Config *config;

using namespace std;

void* play_video( void *p );
int main(int argc, char* argv[], char *envp[] )
{
    config = new Config( argc, argv, envp );

    pthread_t t_mqtt;
    pthread_create(&t_mqtt, NULL, mqtt_loop, NULL);

    Player*     player  = new Player( config->get_name() );
    player->add_filter(config->get_filter());
    player->add_imgsrc(config->get_video());

    cv::startWindowThread();
    pthread_t t_player;
    pthread_create(&t_player, NULL, &play_video, player);
    cv::destroyAllWindows();
    
    pthread_join(t_mqtt, NULL);
    pthread_join(t_player, NULL);

    cout << "Goodbye, all done. " << endl;
    exit(0);
}


void *play_video( void *p )
{
    Player *player = (Player *) p;
    player->play( );
    return p;
}

