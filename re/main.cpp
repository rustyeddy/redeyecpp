#include <iostream>
#include <thread>

#include <opencv2/opencv.hpp>

#include "config.hpp"
#include "mqtt.hpp"
#include "player.hpp"
#include "video.hpp"
#include "filters/filter.hpp"

using namespace std;

MQTTClient *mqtt = NULL;

void *play_video( void *p )
{
    Player *player = (Player *) p;
    player->play( );
    return p;
}

int main(int argc, char* argv[], char *envp[] )
{
    Config *config = new Config( argc, argv, envp );

    MQTTClient* mqtt    = new MQTTClient();
    Player*     player  = new Player( config->get_name() );

    player->add_filter(config->get_filter());
    player->add_imgsrc(config->get_video());

    int rc = mqtt->connect();
    if (rc < 0) {
        clog << "MQTT Error connecting to broker, run without broker" << endl;
        delete mqtt;
        mqtt = NULL;
    }

    cv::startWindowThread();

    pthread_t t_player;
    pthread_create(&t_player, NULL, &play_video, player);

    if ( mqtt ) {
        cout << "Mosquitto loop " << endl;
        rc = mosquitto_loop( mqtt->get_mosq(), -1, -1 );
    }



    pthread_join(t_player, NULL);
    cv::destroyAllWindows();
    cout << "Goodbye, all done. " << endl;
}
