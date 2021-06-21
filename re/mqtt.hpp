#pragma once

#include <string>

#include <mosquitto.h>


class MQTTClient
{
private:
    struct mosquitto    *_mosq = NULL;
    char*       _mqtt_broker = (char *)"10.24.10.10";

public:
    MQTTClient();
    ~MQTTClient();

    struct mosquitto    *get_mosq() { return _mosq; }

    int connect();
    int publish(std::string topic, std::string msg);
    int subscribe( std::string topic, void *callback(void *p) );

};

extern MQTTClient *mqtt;
