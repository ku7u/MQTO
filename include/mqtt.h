// ensure this library description is only included once
#ifndef MQTT_H
#define MQTT_H


#include <Arduino.h>
#include <PubSubClient.h>

// library interface description
class MQTT
{
public:
  // constructors:
  MQTT(void);

  void connect(PubSubClient *client);
  void subscribe(PubSubClient* client, String leftend);

private:
  String _mqttNodeName;
  String _mqttServer;
  char* _mqttnode;
  IPAddress _ip;

};

#endif