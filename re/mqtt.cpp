#include <string>
#include <string.h>
#include <iostream>

#include <mosquitto.h>

using namespace std;

string _mqtt_broker = "tcp://10.24.10.10:1883";


int mqtt_connect()
{
    struct mosquitto *mosq;
    int rc = 1;
    
    mosquitto_lib_init();
    mosq = mosquitto_new("pub-test", true, NULL);

    rc = mosquitto_connect(mosq, "10.24.10.10", 1883, 60) ;
    if (rc != 0) {
        clog << "Error failed to connect to MQTT broker: " << endl;
        mosquitto_destroy(mosq);
        return -1;
    }

    clog << "Connected to the MQTT broker!" << endl;

    mosquitto_publish(mosq, NULL, "redeye/announce/camera-99", 5, "Hello", 0, false);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);

    mosquitto_lib_cleanup();
    return rc;    
}
