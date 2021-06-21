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

    int connect();
    int publish(std::string topic, std::string msg);
};


extern int mqtt_connect();
