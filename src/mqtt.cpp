#include "mqtt.h"
#include <PubSubClient.h>
#include <Preferences.h>

MQTT::MQTT(void)
{
  Preferences myPrefs;

  // _mqttServer = server;
  // _mqttNodeName = node;

  // myPrefs.begin("network", true);
  // _mqttServer = myPrefs.getString("mqttserver", "192.168.0.254");
  // _mqttNodeName = myPrefs.getString("mqttnodename", "TestNode");
  // myPrefs.end();

  // char mqttserver[_mqttServer.length() + 1]; // converting from string to char array required for client parameter
  // strcpy(mqttserver, _mqttServer.c_str());
  // sscanf(mqttserver, "%u.%u.%u.%u", &_ip[0], &_ip[1], &_ip[2], &_ip[3]);
}

void MQTT::connect(PubSubClient *client)
{
  // TBD this could be reworked to provide noticing a server ip change
  Preferences myPrefs;

  myPrefs.begin("general", true);
  _mqttServer = myPrefs.getString("mqttserver", "192.168.0.254");
  // _mqttNodeName = myPrefs.getString("mqttnodename", "TestNode");
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

  // // accept all <topic left end>/<node>/<device> topics
  // // they will be of the form trains/track/turnout/<JMRI system name> THROWN/CLOSED
  // // JMRI system name must be nodename + "/" + device name

  // // feedback (not a subscription) is of the form trains/track/sensor/turnout/<JMRI system name> ACTIVE/INACTIVE

  myPrefs.begin("general", true);
  turnoutTopic = myPrefs.getString("leftend", "cmd/mqto/");
  myPrefs.end();

  turnoutTopic = turnoutTopic + nodeName;

  strcpy(subscription, turnoutTopic.c_str());
  client->subscribe(subscription, 1);
}

/*****************************************************************************/
// defines the connection parameters, the callback, the subscriptions and then connects
void mqttSetup(String mqtt_Server, String iobNode)
{
  // char mqtt_server[mqtt_Server.length() + 1]; // converting from string to char array required for client parameter
  // strcpy(mqtt_server, mqtt_Server.c_str());
  // Serial.print("mqtt_server ");
  // Serial.println(mqtt_server);
  // uint8_t ip[4];
  // // int ip[4];
  // sscanf(mqtt_server, "%u.%u.%u.%u", &ip[0], &ip[1], &ip[2], &ip[3]);
  // client.setServer(ip, 1883); // 1883 is the default port on mosquitto server
  // // client.setKeepAlive(60);    // this is probaably not necessary, just use the default
  // // client.setCallback(callback);
  // connectMQTT(iobNode);
  // setupSubscriptions();
}

/*****************************************************************************/
// void setupSubscriptions(PubSubClient *client, String nodeName)
// {
//   Preferences myPrefs;
//   char subscription[100];
//   String turnoutTopic;

//   // // accept all <topic left end>/<node>/<device> topics
//   // // they will be of the form trains/track/turnout/<JMRI system name> THROWN/CLOSED
//   // // JMRI system name must be nodename + "/" + device name

//   // // feedback (not a subscription) is of the form trains/track/sensor/turnout/<JMRI system name> ACTIVE/INACTIVE

//   myPrefs.begin("topics", true);
//   turnoutTopic = myPrefs.getString("leftend", "trains/track/turnout/");
//   myPrefs.end();

//   turnoutTopic = turnoutTopic + nodeName + "/";
//   // turnoutFeedbackTopic = topicFeedbackLeftEnd + nodeName + "/";

//   strcpy(subscription, turnoutTopic.c_str());
//   client->subscribe(subscription, 1);
// }
