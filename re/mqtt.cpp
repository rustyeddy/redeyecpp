#include <string>
#include <string.h>
#include <iostream>

#include <mosquitto.h>

#include "mqtt.hpp"

using namespace std;

string _mqtt_broker = "tcp://10.24.10.10:1883";

void connect_callback(struct mosquitto *mosq, void *obj, int result);
void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *mesg);

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

    mosquitto_connect_callback_set( _mosq, connect_callback );
    int rc = mosquitto_connect( _mosq, "10.24.10.10", 1883, 60 ) ;
    if (rc != 0) {
        clog << "Error failed to connect to MQTT broker: " << endl;
        mosquitto_destroy(_mosq);
        return -1;
    }
    clog << "Connection request to the MQTT broker!" << endl;
    return 0;
}

int MQTTClient::publish(string topic, string msg)
{
    return mosquitto_publish( _mosq, NULL, topic.c_str(), msg.length(), msg.c_str(), 0, false );
}

int MQTTClient::subscribe( string topic, void *callback(void *p) )
{
    return 0;
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
    clog << "Connected to the MQTT broker!" << endl;
    mqtt->publish("redeye/announce/camera", "camera99");
    mosquitto_subscribe( mqtt->get_mosq(), NULL, "redeye/camera/camera99", 0);
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    bool match = 0;
    printf("MQTT Message topic: %d - %s - %s\n", msg->payloadlen, (char *) msg->payload, msg->topic);
}
