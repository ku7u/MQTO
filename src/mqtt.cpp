#include "mqtt.h"
#include <PubSubClient.h>
#include <Preferences.h>

MQTT::MQTT(void)
{
}

void MQTT::connect(PubSubClient *client)
{
  // TBD this could be reworked to provide noticing a server ip change
  Preferences myPrefs;

  myPrefs.begin("general", true);
  _mqttServer = myPrefs.getString("mqttserver", "192.168.0.254");
  myPrefs.end();

  char mqttserver[_mqttServer.length() + 1]; // converting from string to char array required for client parameter
  strcpy(mqttserver, _mqttServer.c_str());
  sscanf(mqttserver, "%u.%u.%u.%u", &_ip[0], &_ip[1], &_ip[2], &_ip[3]);

  char mqttnode[_mqttNodeName.length() + 1];
  strcpy(mqttnode, _mqttNodeName.c_str());
  client->setServer(_ip, 1883); // 1883 is the default port on mosquitto server

  // Loop until we're reconnected
  while (!client->connect(mqttnode))
  {
    Serial.print("Failed to connect to ");
    Serial.print(_mqttServer);
    Serial.print(" Response was ");
    Serial.println(client->state());
    Serial.println("Retrying.");

    // Wait 1 second before retrying
    delay(1000);
  }

  Serial.println("mqtt connected");
}

void MQTT::subscribe(PubSubClient *client, String nodeName)
{
  Preferences myPrefs;
  char subscription[100];
  String turnoutTopic;

  myPrefs.begin("general", true);
  turnoutTopic = myPrefs.getString("leftend", "cmd/mqto/");
  myPrefs.end();

  turnoutTopic = turnoutTopic + nodeName;

  strcpy(subscription, turnoutTopic.c_str());
  client->subscribe(subscription, 1);
}


