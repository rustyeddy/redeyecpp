#include <iostream>
#include <thread>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "camera.hpp"
#include "config.hpp"
#include "mqtt.hpp"
#include "net.hpp"
#include "player.hpp"
#include "video.hpp"
#include "web.hpp"

#include "filters/filter.hpp"

Config*         config  = NULL;
Player*         player  = NULL;
FltFilters*     filters = NULL;

Cameras         cameras;

string IP       = "";

using namespace std;

void* hello_loop(void *);

int main(int argc, char* argv[], char *envp[] )
{
    config = new Config( argc, argv, envp );

    // TODO: this will need to be fixed for other machines
    IP = get_ip_address(config->get_iface()); 
    
    // Camera *cam = new Camera(config->get_camera_name());
    // assert(cam);
    cameras.add("video0", new Camera("/dev/video0", "video0"));
    cameras.add("video1", new Camera("/dev/video1", "video1"));
    cameras.add("csi0", new Camera("csi0"));
    cameras.add("csi1", new Camera("csi1"));

    cout << cameras.to_json() << endl;

    //cout << cameras->to_string() << endl;
    //cout << cameras->to_json() << endl;    

#ifdef NOTNOW
    filters = new FltFilters();
    pthread_t t_mqtt;
    pthread_t t_player;
    pthread_t t_web;
    pthread_t t_hello;
    
    pthread_create(&t_mqtt, NULL, mqtt_loop, (char *)ID.c_str());
    pthread_create(&t_web,  NULL, web_start, NULL);
    pthread_create(&t_hello, NULL, hello_loop, NULL);

    player  = new Player( config->get_filter_name() );
    player->set_filter( config->get_filter_name() );
    player->add_imgsrc( config->get_video() );

    cv::startWindowThread();
    pthread_create(&t_player, NULL, &play_video, player);
    cv::destroyAllWindows();

    pthread_join(t_player, NULL);     

    pthread_join(t_web, NULL);
    pthread_join(t_mqtt, NULL);
    pthread_join(t_hello, NULL);
#endif // NOTNOW

    cout << "Goodbye, all done. " << endl;
    exit(0);
}

void* hello_loop(void *)
{
    int running = true;

    string jstr = "{";
    jstr += "\"addr\":\"" + IP + "\",";
    jstr += "\"port\":" + to_string(config->get_mjpg_port()) + ",";
    jstr += "\"name\":\"" + IP + "\",";
    jstr += "\"uri\": \"" + config->get_video_uri() + "\"";
    jstr += "}";

    while (running) {
        sleep(10);              // announce every 10 seconds
        mqtt_publish("redeye/announce/camera", jstr.c_str());
    }
    return NULL;
}
