#include <string>
#include <string.h>
#include <iostream>

#include <mosquitto.h>

#include "mqtt.hpp"

using namespace std;

string _mqtt_broker = "tcp://10.24.10.10:1883";

MQTTClient::MQTTClient()
{
}

MQTTClient::~MQTTClient()
{
    mosquitto_disconnect(_mosq);
    mosquitto_destroy(_mosq);

    mosquitto_lib_cleanup();
}

int MQTTClient::connect()
{
    mosquitto_lib_init();
    _mosq = mosquitto_new("redeye", true, NULL);

    int rc = mosquitto_connect(_mosq, "10.24.10.10", 1883, 60) ;
    if (rc != 0) {
        clog << "Error failed to connect to MQTT broker: " << endl;
        mosquitto_destroy(_mosq);
        return -1;
    }
    clog << "Connected to the MQTT broker!" << endl;
    return 0;
}

int MQTTClient::publish(string topic, string msg)
{
    string s("redeye");
    return mosquitto_publish( _mosq, NULL, topic.c_str(), msg.length(), msg.c_str(), 0, false );
}
