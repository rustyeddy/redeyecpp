#include <iostream>
#include <thread>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "mqtt.hpp"
#include "net.hpp"
#include "player.hpp"
#include "video.hpp"
#include "filters/filter.hpp"

Config*         config;
Player*         player;

string ID = "";

using namespace std;

int main(int argc, char* argv[], char *envp[] )
{
    config = new Config( argc, argv, envp );

    // TODO: this will need to be fixed for other machines
    ID = get_ip_address("eno1"); 

    pthread_t t_mqtt;
    pthread_t t_player;
    
    pthread_create(&t_mqtt, NULL, mqtt_loop, (char *)ID.c_str());

    player  = new Player( config->get_filter_name() );
    player->set_filter( config->get_filter_name() );
    player->add_imgsrc( config->get_video() );

    cv::startWindowThread();

    // player will create an event loop for commands and handle
    // player messaging 
    pthread_create(&t_player, NULL, &play_video, player);

    cv::destroyAllWindows();
    
    pthread_join(t_mqtt, NULL);
    pthread_join(t_player, NULL); 

    cout << "Goodbye, all done. " << endl;
    exit(0);
}
