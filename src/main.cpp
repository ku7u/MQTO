
/*
MIT License

Copyright (c) 2022 George Hofmann

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

ToDo:

  Pin assignments:
   01  TX0
   02
   03  RX0
   04  GPIO reserved for neopixel output
   05  switch for configuration via bluetooth
   12  A+ stepper 1
   13  A- stepper 1
   14  B+ stepper 1
   15  B- stepper 1
   16  A+ stepper 2
   17  A- stepper 2
   18  B+ stepper 2
   19  B- stepper 2
   21  A+ stepper 3
   22  A- stepper 3
   23  B+ stepper 3
   25  B- stepper 3
   26  A+ stepper 4
   27  A- stepper 4
   32  B+ stepper 4
   33  B- stepper 4
   34  switch 1 requires pullup on board
   35  switch 2 requires pullup on board
   36  switch 3 requires pullup on board
   39  switch 4 requires pullup on board
   */

#include <Arduino.h>
#include <iostream>
#include "ESPAsyncWebServer.h"
#include <SPIFFS.h>
#include "AsyncTCP.h"
#include "ESPConnect.h"
#include "AsyncElegantOTA.h"
#include <esp_timer.h>
#include <Preferences.h>
#include <PubSubClient.h>
#include "WiFi.h"
#include "mqtt.h"
#include <Adafruit_NeoPixel.h>
#include "StepperMRTO.h"
#include "oldstuff.h"
// #define testing

using namespace std;

const char *version = "2.2.0";

Preferences myPrefs;
char *deviceSpace[] = {"d1", "d2", "d3", "d4"};

// wifi
WiFiClient espClient;
String SSID;
String wifiPassword;
AsyncWebServer server(80);

// mqtt
MQTT mqtt;
String mqttServer;
String mqttNode;
String topicLeftEnd;
String topicFeedbackLeftEnd;
String turnoutTopic;
String turnoutFeedbackTopic;
PubSubClient mqttClient(espClient);

const char *TOPIC_INPUT_1 = "input1";
const char *TOPIC_INPUT_2 = "input2";
const char *TOPIC_INPUT_3 = "input3";
const char *TOPIC_INPUT_4 = "input4";

String nodeName;

// constants and variables - turnouts
uint16_t const NUM_DEVICES = 4;
String devName[NUM_DEVICES];
uint16_t const STEPS_PER_REVOLUTION = 20; // number of steps per revolution
uint16_t const NOMINAL_SPEED = 1000;
uint16_t const NOMINAL_STROKE = 500;
uint16_t const NOMINAL_TORQUE_INTERVAL = 500;

// motor pins
uint16_t const APlus1Pin = 12;
uint16_t const AMinus1Pin = 13;
uint16_t const BPlus1Pin = 14;
uint16_t const BMinus1Pin = 15;

uint16_t const APlus2Pin = 16;
uint16_t const AMinus2Pin = 17;
uint16_t const BPlus2Pin = 18;
uint16_t const BMinus2Pin = 19;

uint16_t const APlus3Pin = 21;
uint16_t const AMinus3Pin = 22;
uint16_t const BPlus3Pin = 23;
uint16_t const BMinus3Pin = 25;

uint16_t const APlus4Pin = 26;
uint16_t const AMinus4Pin = 27;
uint16_t const BPlus4Pin = 32;
uint16_t const BMinus4Pin = 33;

StepperMRTO myStepper[] =
    {StepperMRTO(STEPS_PER_REVOLUTION, APlus1Pin, AMinus1Pin, BPlus1Pin, BMinus1Pin),
     StepperMRTO(STEPS_PER_REVOLUTION, APlus2Pin, AMinus2Pin, BPlus2Pin, BMinus2Pin),
     StepperMRTO(STEPS_PER_REVOLUTION, APlus3Pin, AMinus3Pin, BPlus3Pin, BMinus3Pin),
     StepperMRTO(STEPS_PER_REVOLUTION, APlus4Pin, AMinus4Pin, BPlus4Pin, BMinus4Pin)};

// switch pins for manual control, these must have pullup resistors
uint16_t const switchPin[4] = {34, 35, 36, 39};
bool switchesAvailable = false; // change to true from menu iff switch pins have pullups

bool returnToMenu = false; // for test actuation feature from menu

// neoPixels
#define LED_PIN 4
#define LED_COUNT 4
uint32_t red;
uint32_t yellow;
uint32_t green;
uint32_t blue;
uint32_t dark = 0;
bool flasher;           // used to flash the yellow light while moving
uint32_t lastFlashTime; // for flasher

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t testTimer;
uint32_t testCounter;

/*****************************************************************************/
// each push of a switch activaates the device to move in direction opposite to last commanded
void checkSwitches()
{
  for (int i = 0; i < NUM_DEVICES; i++)
  {
    // if corresponding stepper is in ready state or is running just skip it (debounces the switch)
    if ((digitalRead(switchPin[i]) == LOW) && (!myStepper[i].getRunState()) && (!myStepper[i].getReadyState()))
    {
      switch (myStepper[i].getLastCommanded())
      {
      case 0:
        myStepper[i].setReady(1);
        break;
      case 1:
        myStepper[i].setReady(0);
        break;
      default:
        myStepper[i].setReady(1);
        break;
      }
      return;
    }
  }
}

/*****************************************************************************/
// looks for steppers that are ready to run and runs them, one at a time (to limit current)
// this routine must be called repeatedly in the loop
bool runSteppers() // returns true if a throw was completed, false otherwise
{
  // bool throwComplete = false;
  String feedbackTopic;

  for (int i = 0; i < NUM_DEVICES; i++)
  {
    if (myStepper[i].getRunState()) // returns false if not in running state
    {
      if (myStepper[i].run()) // true if completed
      {
        feedbackTopic = turnoutFeedbackTopic + devName[i];
        if (myStepper[i].getLastCommanded())
        {
          mqttClient.publish(feedbackTopic.c_str(), "ACTIVE");
          strip.setPixelColor(i, red);
        }
        else
        {
          mqttClient.publish(feedbackTopic.c_str(), "INACTIVE");
          strip.setPixelColor(i, green);
        }
        strip.show();
        return true;
      }
      // flash the yellow when in motion
      if (millis() - lastFlashTime > 100)
      {
        lastFlashTime = millis();
        if (flasher)
          strip.setPixelColor(i, yellow);
        else
          strip.setPixelColor(i, 0);
        flasher = !flasher;
        strip.show();
      }
      return false; // if it did run don't try to run any others
    }
  }

  // if we got here nothing was running so check for steppers that are ready and set the first found to run
  for (int i = 0; i < NUM_DEVICES; i++)
  {
    if (myStepper[i].getReadyState())
    {
      // the first one we find that is ready we set to run and then exit
      myStepper[i].run();
      // strip.setPixelColor(i, yellow);
      // strip.show();
      break;
    }
  }

  return false;
}

/*****************************************************************************/
// this is a callback from the mqtt object, made when a subscribed message comes in
// we only expect four topics that were subscribed so only need to check the last part which is the device
void callback(char *topic, byte *message, unsigned int length)
{
  String topicString;
  String lastPart;
  char messChars[50];

  topicString = String(topic);

  for (int i = 0; i < length; i++)
    messChars[i] = (char)message[i];
  messChars[length] = '\0';

  lastPart = topicString.substring(topicString.lastIndexOf('/') + 1);

  for (int i = 0; i < NUM_DEVICES; i++)
  {
    if (lastPart.equals(devName[i]))
    {
      if (strcmp(messChars, "THROWN") == 0)
      {
        myStepper[i].setReady(1);
        // BTSerial.println("Thrown received");
      }
      if (strcmp(messChars, "CLOSED") == 0)
      {
        myStepper[i].setReady(0);
        // BTSerial.println("Closed received");
      }
    }
  }
}

/*****************************************************************************/
void setup()
{

  Serial.begin(115200);
  SPIFFS.begin(true);

  // Configure SSID and password for Captive Portal
  String SSID = "Loco_" + String(1);
  ESPConnect.autoConnect(SSID.c_str()); // TBD use the actual roadnum

  // Begin connecting to previous WiFi or start autoConnect AP if unable to connect
  if (ESPConnect.begin(&server))
  {
    Serial.println("Connected to WiFi");
    Serial.println("IPAddress: " + WiFi.localIP().toString());
  }
  else
  {
    Serial.println("Failed to connect to WiFi");
  }

  // start neoPixels and set all to blue
  // neoPixels must be wired in order of devices, first nP is device 1
  strip.begin();
  red = strip.gamma32(strip.ColorHSV(0, 200, 70));
  yellow = strip.gamma32(strip.ColorHSV((65536 / 6) - 1500, 255, 100)); // a little brighter and yellower
  green = strip.gamma32(strip.ColorHSV(65536 / 3, 200, 70));
  blue = strip.gamma32(strip.ColorHSV(65536 * 2 / 3, 200, 70));
  for (int i = 0; i < NUM_DEVICES; i++)
    strip.setPixelColor(i, blue);
  strip.show();

  // get the stored configuration values, defaults are the second parameter in the list
  myPrefs.begin("general");
  switchesAvailable = myPrefs.getBool("switchesavailable", false); // check for panel switches in use
  // nodeName = myPrefs.getString("nodename", "MQTTtosNode");
  // SSID = myPrefs.getString("SSID", "none");
  // wifiPassword = myPrefs.getString("wifipassword", "none");
  // mqttServer = myPrefs.getString("mqttserver", "none");
  // topicLeftEnd = myPrefs.getString("topicleftend", "trains/track/turnout/");
  // topicFeedbackLeftEnd = myPrefs.getString("topicfeedbackleftend", "trains/track/sensor/turnout/");
  myPrefs.end();

  // turnout specific
  // read the stored values for speed, throw, torque and reversed
  // defaults are the second parameter in the list
  // send those values to the stepper objects
  for (int i = 0; i < NUM_DEVICES; i++)
  {
    myPrefs.begin(deviceSpace[i]);
    devName[i] = myPrefs.getString("name", "noname");
    Serial.println(devName[i]);

    // set the rotational speed using rpm as parameter, defaults to NOMINAL_SPEED
    myStepper[i].setSpeed(myPrefs.getUShort("speed", NOMINAL_SPEED));

    // set the length of the stroke, defaults to NOMINAL_STROKE
    // nominal value of 500 should be enough for most turnouts
    // it could be made less through experimentation
    myStepper[i].setStrokeSteps(myPrefs.getUShort("throw", NOMINAL_STROKE));

    // limit the torque, defaults to NOMINAL_TORQUE_INTERVAL
    // this defines the time in microseconds that current current flow will be shortened in each step
    // the default is 500, a smaller number provides more torque but consumes more current
    // at 1000 rpm the step length is 3000 ms for a 20 step/revolution motor
    myStepper[i].setTorqueLimit(myPrefs.getUShort("force", NOMINAL_TORQUE_INTERVAL));

    // configure the direction, defaults to false (non-reversed)
    // design assumes device is installed on the closed side of turnout and that turnout is closed
    // the first movement after startup will be to pull the throwbar thus throwing the track switch
    // setting reversed to true will set motion to the opposite of above as required if machine is located on diverging side
    // as well, the device may need to be reversed depending on whether coil wires are reversed
    // bottom line is to set the reversed parameter to make the device work as expected
    myStepper[i].setReversed(myPrefs.getBool("reversed", false));
    myPrefs.end();
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html", false); });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/topics.html", "text/html", false); });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/network.html", "text/html", false); });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/stylesheet.css", "text/css", false); });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String inputMessage;
              String inputParam;
              // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
              if (request->hasParam(TOPIC_INPUT_1))
              {
                inputMessage = request->getParam(TOPIC_INPUT_1)->value();
                inputParam = TOPIC_INPUT_1;
              }
              // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
              else if (request->hasParam(TOPIC_INPUT_2))
              {
                inputMessage = request->getParam(TOPIC_INPUT_2)->value();
                inputParam = TOPIC_INPUT_2;
              }
              // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
              else if (request->hasParam(TOPIC_INPUT_3))
              {
                inputMessage = request->getParam(TOPIC_INPUT_3)->value();
                inputParam = TOPIC_INPUT_3;
              }
              // GET input4 value on <ESP_IP>/get?input4=<inputMessage>
              else if (request->hasParam(TOPIC_INPUT_4))
              {
                inputMessage = request->getParam(TOPIC_INPUT_4)->value();
                inputParam = TOPIC_INPUT_4;
              }              
              else
              {
                inputMessage = "No message sent";
                inputParam = "none";
              }
              Serial.println(inputMessage);

              request->send(SPIFFS, "/topics.html", "text/html", false); });

  // following from codeproject
  server.serveStatic("/", SPIFFS, "/");

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();

  // MQTT
  // MQTT mqtt;
  mqtt.connect(&mqttClient);
  mqtt.subscribe(&mqttClient, "WinlockNorthSiding");
  mqttClient.setCallback(callback);
}

/*****************************************************************************/
void loop()
{
  if (!mqttClient.connected())
  {
    mqtt.connect(&mqttClient);
    //   setupSubscriptions();
  }

  mqttClient.loop();

  // if (switchesAvailable)
  //   checkSwitches();

  // if (runSteppers() && returnToMenu) // runSteppers returns true at end of throw, check if throw was commanded from menu
  // {
  //   returnToMenu = false; // we came here from the menu 'A' command, return to menu
  //   configure();          // TBD this is different now
  // }
}