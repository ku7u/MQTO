// ensure this library description is only included once
#ifndef MQTT_H
#define MQTT_H


#include <Arduino.h>
#include <PubSubClient.h>
#include <Preferences.h>

// library interface description
class MQTT
{
public:
  // constructors:
  MQTT(void);

  void setup(PubSubClient *client, String mqtt_Server, String node);
  void connect(PubSubClient *client);
  void subscribe(PubSubClient* client, String leftend);

private:
  String _mqttNodeName;
  String _mqttServer;
  char* _mqttnode;
  IPAddress _ip;
  // Preferences _mqttPreferences;

};

void mqttSetup(String mqtt_Server, String iobNode);
void connectMQTT();
void setupSubscriptions();

#endif