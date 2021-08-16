#include <iostream>
#include <thread>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "camera.hpp"
#include "config.hpp"
#include "event.hpp"
#include "mqtt.hpp"
#include "net.hpp"
#include "player.hpp"
#include "video.hpp"
#include "web.hpp"

#include "filters/filter.hpp"

using namespace std;

Config*         config  = NULL;
Player*         player  = NULL;
FltFilters*     filters = NULL;

Cameras         cameras;
queue<Event*>   eventQ;

string IP       = "";

void  main_loop();
void* hello_loop(void *);

int main(int argc, char* argv[], char *envp[] )
{
    config = new Config( argc, argv, envp );

    // TODO: this will need to be fixed for other machines
    IP = get_ip_address(config->get_iface()); 
    
    cameras.add("video0", new Camera("video0"));
    cameras.add("video1", new Camera("video1"));
    cameras.add("csi0", new Camera("csi0"));
    cameras.add("csi1", new Camera("csi1"));

    string name = config->get_camera_name();

    if ( config->Debug ) {
        cout << "Camera list" << endl;
        cout << cameras.to_json() << endl;
        cout << "Current Camera: " << name << endl;
        cout << "Checkout camera " << name << endl;
    }
    
    if ( name != "" ) {
        Event *e = new Event(EVENT_CAMERA_PLAY, name );
        eventQ.push(e);
    }
    main_loop();

  done:
    cout << "Goodbye, all done. " << endl;
    exit(0);
}

void main_loop()
{
    pthread_t t_mqtt;
    pthread_t t_web;    
    pthread_t t_hello;

    pthread_create(&t_mqtt, NULL, mqtt_loop, (char *)IP.c_str());
    pthread_create(&t_web,  NULL, web_start, NULL);
    pthread_create(&t_hello, NULL, hello_loop, NULL);

    filters = new FltFilters();

    // This program will wait for explicit instruction to start
    // streams from one or more of our cameras.
    
    bool running = true;
    while ( running ) {
        Camera* cam = NULL;
        string camname = "";

        if ( eventQ.empty() ) {
            usleep(100);
            continue;
        }

        Event* e = eventQ.front();
        eventQ.pop();

        switch (e->get_type()) {

        case EVENT_CAMERA_PLAY:

            camname = e->get_camera();
            cam = cameras.get( camname );
            if (cam == NULL) {
                cout << "Error opening " + camname << endl;
                break;
            }

            //cam->play();
            // start a thread

            player = new Player(cam);
            player->play();
            break;

        case EVENT_CAMERA_PAUSE:

            cam = cameras.get(e->get_camera());
            if (cam == NULL) {
                // error bad camera name
                break;
            }
            cam->pause();
            break;
            
        case EVENT_FILTER:
            cam = cameras.get(e->get_camera());
            if (cam == NULL) {
                // error bad camera name
                break;
            }
            cam->set_filter(e->get_args());
            break;

        case EVENT_EXIT:

            running = false;

            break;

        default:
            // get mad and send an error

            break;

        }

    }

    pthread_join(t_hello, NULL);
    pthread_join(t_web, NULL);
    pthread_join(t_mqtt, NULL);

}

void* hello_loop(void *)
{
    int running = true;
    json j;

    while (running) {
        sleep(10);              // announce every 10 seconds
        j = cameras.to_json();
        auto ipaddr = IP.c_str();
        string chan("redeye/annouce/camera");
        chan += "/" + IP;
        mqtt_publish(chan.c_str(), j.dump());
    }
    return NULL;
}
