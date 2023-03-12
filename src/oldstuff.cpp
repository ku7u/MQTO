#include <Arduino.h>
#include "oldstuff.h"

// extern BlueToothSerial BTSerial;

/*****************************************************************************/
// get rid of unseen characters in buffer
void flushSerialIn(void)
{
//   while (BTSerial.available() > 0)
//   { // clear the buffer
//     delay(5);
//     BTSerial.read();
//   }
}

/*****************************************************************************/
bool timeout(uint32_t myTime)
{
  if (millis() - myTime > 30000)
    // disconnect if no action from operator for 30 seconds
    return true;
  else
    return false;
}

// /*****************************************************************************/
// // get rid of unseen characters in buffer
// void flushSerialIn(void)
// {
//   while (BTSerial.available() > 0)
//   { // clear the buffer
//     delay(5);
//     BTSerial.read();
//   }
// }

// configure the MQTT server ip address
void setMQTT()
{
  // String myString;
  // // BTSerial.print("\nEnter MQTT server IP address: ");
  // // while (!BTSerial.available())
  // // {
  // // }
  // // myString = BTSerial.readString();
  // myString.trim();
  // if (myString.length() == 0)
  //   return;
  // myPrefs.begin("general", false);
  // myPrefs.putString("mqttserver", myString);
  // myPrefs.end();
  // BTSerial.print("Changed to ");
  // BTSerial.println(myString);
  // BTSerial.println("\nReboot is required");
  // return;
}

/*****************************************************************************/
// gets one character and converts to upper case, clears input buffer of C/R and newline
// char getUpperChar(uint32_t invokeTime)
// {
  // char _myChar;

  // while (true)
  // {
  //   if (invokeTime > 0)
  //   {
  //     if (timeout(invokeTime))
  //       return ' '; // operator dozed off
  //   }

  //   if (BTSerial.available() > 0)
  //   {
  //     delay(5);
  //     _myChar = BTSerial.read();

  //     if (_myChar > 96)
  //       _myChar -= 32;

  //     flushSerialIn();
  //     return _myChar;
  //   }
  // }
  
// }

/*****************************************************************************/
// returns an integer within specified limits
// int getNumber(int min, int max)
// {
  // int _inNumber;

  // while (true)
  // {
  //   if (BTSerial.available() > 0)
  //   {
  //     _inNumber = BTSerial.parseInt();

  //     if ((_inNumber < min) || (_inNumber > max))
  //     {
  //       BTSerial.println(F("Out of range, reenter"));
  //       flushSerialIn();
  //     }
  //     else
  //     {
  //       flushSerialIn();
  //       return _inNumber;
  //     }
  //   }
  // }
// }

/*****************************************************************************/
void printMsg(char *msg)
{
  // BTSerial.println(msg);
}

/*****************************************************************************/
// tests password

// bool pwCheck()
// {
// }

/*****************************************************************************/
void printBinary(uint8_t binVal)
{
  // BTSerial.println(binVal, HEX);
}

/*****************************************************************************/
void print32(uint32_t Val)
{
  // BTSerial.println(Val);
}

/*****************************************************************************/
// displays the menu for user interaction for configuration or testing
void showMenu()
{
  // static bool beenDone;
  // BTSerial.println(" ");
  // BTSerial.print("\nTurnout Controller Main Menu for ");
  // BTSerial.println(BTname);
  // BTSerial.println("\n Enter: ");
  // BTSerial.println(" 'P' - Print status");
  // BTSerial.println(" 'N' - Set node name (Bluetooth and MQTT)");
  // BTSerial.println(" 'X' - Set Bluetooth password");
  // BTSerial.println(" 'W' - Set WiFi credentials");
  // BTSerial.println(" 'M' - Set MQTT server IP address");
  // BTSerial.println(" 'L' - Set left side of topic");
  // BTSerial.println(" 'Y' - Enable/Disable switches");
  // BTSerial.println(" 'T' - Set turnout name(s)");
  // BTSerial.println(" 'S' - Set stepper parameters");
  // BTSerial.println(" 'A' - Actuate a stepper for testing");
  // BTSerial.println(" 'Z' - Turn off Bluetooth until pin 5 reset");
  // // BTSerial.println(" 'D' - Debug display on/off");
  // BTSerial.println(" 'B' - Restart machine");

  // if (!beenDone)
  // {
  //   BTSerial.print("\n Menu choices are not case sensitive");
  //   beenDone = true;
  // }
  // BTSerial.println("\n Enter empty line to return to run mode \n (automatic after 30 sec of inactivity)");
}

/*****************************************************************************/
// business end of the menu
void configure()
{
  //   uint16_t devID;
  //   uint16_t paramVal;
  //   uint16_t enteredVal;
  //   uint16_t _turnoutNumber;
  //   bool paramBool;
  //   String pw;
  //   String myString;
  //   bool beenHereDoneThat = false;
  //   char myChar;
  //   IPAddress ipAdr;
  //   bool changed;

  //   while (true)
  //   {
  //     if (!beenHereDoneThat)
  //     {
  //       showMenu();
  //       beenHereDoneThat = true;
  //     }
  //     else
  //       BTSerial.println("\nMain menu\n Enter 'R' to review menu, empty line to exit");

  //     switch (getUpperChar(millis()))
  //     {

  //     case 'T': // turnout names
  //       while (true)
  //       {
  //         BTSerial.print("\nTurnout naming menu\n Enter turnout number (1 - 4), empty line to exit: ");
  //         _turnoutNumber = getNumber(0, NUM_DEVICES);
  //         if (_turnoutNumber <= 0)
  //           break;
  //         BTSerial.print("\n Enter name, empty line to exit: ");
  //         while (!BTSerial.available())
  //         {
  //         }
  //         myString = BTSerial.readString();
  //         myString.trim();
  //         if (myString.length() == 0)
  //           break;
  //         devName[_turnoutNumber - 1] = myString;
  //         myPrefs.begin(deviceSpace[_turnoutNumber - 1], false);
  //         myPrefs.putString("name", myString);
  //         myPrefs.end();
  //         BTSerial.print("Changed to ");
  //         BTSerial.println(myString);
  //         break;
  //       }

  //     case 'P':
  //     {
  //       BTSerial.println("\nCurrent configuration");
  //       BTSerial.print(" Firmware version: ");
  //       BTSerial.println(version);
  //       BTSerial.print(" Node name (MQTT and Bluetooth) = ");
  //       BTSerial.println(nodeName);
  //       ipAdr = WiFi.localIP();
  //       BTSerial.print(" Local IP address = ");
  //       BTSerial.println(ipAdr);
  //       BTSerial.print(" SSID = ");
  //       BTSerial.print(SSID);
  //       if (WiFi.status() == WL_CONNECTED)
  //         BTSerial.println(" connected");
  //       else
  //         BTSerial.println(" not connected");
  //       BTSerial.print(" MQTT server = ");
  //       BTSerial.print(mqttServer);
  //       if (mqttClient.connected())
  //         BTSerial.println(" connected");
  //       else
  //         BTSerial.println(" not connected");
  //       BTSerial.print(" MQTT topic header = ");
  //       BTSerial.println(topicLeftEnd);

  //       for (int i = 0; i < NUM_DEVICES; i++)
  //       {
  //         BTSerial.print(" Device ");
  //         BTSerial.print(i + 1);
  //         BTSerial.print(" name = ");
  //         BTSerial.println(devName[i]);
  //       }
  //     }
  //     break;

  //     case 'X':
  //       BTSerial.print("\n Enter new Bluetooth password, empty line to exit ");
  //       while (!BTSerial.available())
  //       {
  //       }
  //       pw = BTSerial.readString();
  //       pw.trim();
  //       if (myString.length() == 0)
  //         break;
  //       myPrefs.begin("general", false);
  //       myPrefs.putString("password", pw);
  //       myPrefs.end();
  //       BTpassword = pw;
  //       BTSerial.print(" Changed to ");
  //       BTSerial.println(pw);
  //       break;

  //     case 'W':
  //       setCredentials();
  //       break;

  //     case 'M':
  //       setMQTT();
  //       break;

  //     case 'N':
  //       BTSerial.println("\n Enter a name for this node (must be unique), empty line  to exit: ");
  //       while (!BTSerial.available())
  //       {
  //       }
  //       myString = BTSerial.readString();
  //       myString.trim();
  //       if (myString.length() == 0)
  //         break;
  //       myPrefs.begin("general", false);
  //       myPrefs.putString("nodename", myString);
  //       myPrefs.end();
  //       BTSerial.print(" Changed to ");
  //       BTSerial.println(myString);
  //       BTSerial.println("\nReboot is required");
  //       break;

  //     case 'L': // set topic left end
  //       changed = false;
  //       BTSerial.print("\n Current topic header: ");
  //       BTSerial.println(topicLeftEnd);
  //       BTSerial.println("\n Enter new topic header or empty line to exit: ");
  //       while (!BTSerial.available())
  //       {
  //       }
  //       myString = BTSerial.readString();
  //       myString.trim();
  //       if (myString.length() != 0)
  //       // break;
  //       {
  //         changed = true;
  //         myPrefs.begin("general", false);
  //         myPrefs.putString("topicleftend", myString);
  //         myPrefs.end();
  //         BTSerial.print("\n Changed to ");
  //         BTSerial.println(myString);
  //       }

  //       BTSerial.print("\n Current feedback topic header: ");
  //       BTSerial.println(topicFeedbackLeftEnd);
  //       BTSerial.println("\n Enter new feedback topic header or empty line to exit: ");
  //       while (!BTSerial.available())
  //       {
  //       }
  //       myString = BTSerial.readString();
  //       myString.trim();
  //       if (myString.length() != 0)
  //       // break;
  //       {
  //         changed = true;
  //         myPrefs.begin("general", false);
  //         myPrefs.putString("topicfeedbackleftend", myString);
  //         myPrefs.end();
  //         BTSerial.print("\n Changed to ");
  //         BTSerial.println(myString);
  //       }
  //       if (changed)
  //         BTSerial.println("\n Reboot is required");
  //       break;

  //     case 'Y': // enable/disable switches
  //       BTSerial.print("\n Enable/Disable manual switches\n");
  //       BTSerial.print(" Pullups must be installed for switches to work!\n");
  //       BTSerial.print(" Enter 'E' or 'D', empty line to exit\n");
  //       myChar = getUpperChar(millis());
  //       if (myChar == 'E')
  //         switchesAvailable = true;
  //       else if (myChar == 'D')
  //         switchesAvailable = false;
  //       else
  //         break;
  //       myPrefs.begin("general", false);
  //       myPrefs.putBool("switchesavailable", switchesAvailable);
  //       myPrefs.end();
  //       break;

  //     case 'S': // stepper configuration
  //       stepperParameters();
  //       break;

  //     case 'A':
  //       BTSerial.print("\n Actuate a turnout motor\n Enter device number (1 - 4): ");
  //       devID = getNumber(1, 4);
  //       myStepper[devID - 1].setReady(!myStepper[devID - 1].getLastCommanded());
  //       returnToMenu = true;
  //       return;

  //     case 'Z':
  //       BTSerial.println(" Turning off Bluetooth, ground pin 5 to reconnect");
  //       BTSerial.println(" Continue? ('Y' or 'N')");
  //       myChar = getUpperChar(30000);
  //       if (myChar != 'Y')
  //         break;
  //       myPrefs.begin("general", false);
  //       myPrefs.putBool("BTon", false);
  //       myPrefs.end();
  //       BTSerial.end();
  //       BTSerial.disconnect();
  //       break;

  //     case 'D':
  //       BTSerial.println(" Turn debug display on ('Y') or off ('N') ");
  //       myChar = getUpperChar(30000);
  //       BTSerial.println(" Which detector (1-8)?");
  //       devID = getNumber(1, 8);
  //       // bod[devID - 1].setDisplayDetect(myChar = 'Y');
  //       break;

  //     case 'R':
  //       beenHereDoneThat = false;
  //       break;

  //     case 'B': // reboot
  //       BTSerial.println("\nDevice will now be rebooted...");
  //       delay(1000);
  //       ESP.restart();
  //       break;

  //     default:
  //       BTSerial.println("\nExiting to run mode");
  //       // delay(1000);
  //       return;
  //     }
  //   }
}

/*****************************************************************************/
// void setup_wifi()
// {
// delay(10);

// char ssid[SSID.length() + 1];
// strcpy(ssid, SSID.c_str());
// char wifipassword[wifiPassword.length() + 1];
// strcpy(wifipassword, wifiPassword.c_str());

// WiFi.begin(ssid, wifipassword);

// if (WiFi.status() != WL_CONNECTED)
//   pinMode(2, OUTPUT);

// uint32_t now = millis();

// while (WiFi.status() != WL_CONNECTED)
// {
//   delay(300);
//   // blink the blue LED to indicate error condition
//   digitalWrite(2, LOW);
//   delay(300);
//   digitalWrite(2, HIGH);

//   if (millis() - now > 5000)
//     break;
// }

// pinMode(2, INPUT_PULLUP);

// if (WiFi.status() == WL_CONNECTED)
// {
//   return;
// }
// else
// {
//   // allow operator to get in via Bluetooth to provide credentials
//   while (true)
//   {
//     // if (BTSerial.available())
//     // {
//     //   flushSerialIn();
//     //   if (pwCheck())
//     //     configure();
//     // }
//   }
// }
// }

/*****************************************************************************/
// shows stepper current values for the parameter passed in
void showCurrentValues(char myChar)
{
  // BTSerial.println(" Current values");
  // for (int i = 0; i < NUM_DEVICES; i++)
  // {
  //   BTSerial.print("  Device ");
  //   BTSerial.print(i + 1);
  //   BTSerial.print("  ");
  //   switch (myChar)
  //   {
  //   case 'S':
  //     BTSerial.println(myStepper[i].getSpeed());
  //     break;

  //   case 'T':
  //     BTSerial.println(myStepper[i].getStrokeSteps());
  //     break;

  //   case 'F':
  //     BTSerial.println(myStepper[i].getTorqueLimit());
  //     break;

  //   case 'D':
  //     BTSerial.println(myStepper[i].getReversed());
  //     break;

  //   default:
  //     break;
  //   }
  // }
}

/*****************************************************************************/
// configure all of the stepper parameters
void stepperParameters()
{
  // uint16_t devID;
  // uint16_t paramVal;
  // bool paramBool;

  // while (true)
  // {
  //   BTSerial.println("\nConfiguration menu for Speed, Throw, Force, Direction\n");
  //   BTSerial.println(" Enter S, T, F or D. Enter empty line to exit");

  //   switch (getUpperChar(millis()))
  //   {
  //   case 'S':
  //     BTSerial.println("\n Speed (rpm, valid value 100 - 2000, default = 1000)");
  //     showCurrentValues('S');
  //     BTSerial.println("\n Enter 'C' to change or empty line  to exit");
  //     if (getUpperChar(millis()) != 'C')
  //       break;
  //     BTSerial.println(" Enter device (1 - 4) or 0 for all");

  //     devID = getNumber(0, 4);
  //     BTSerial.print(" Enter value for ");
  //     if (devID == 0)
  //       BTSerial.println("all devices");
  //     else
  //     {
  //       BTSerial.print("device ");
  //       BTSerial.println(devID);
  //     }
  //     paramVal = getNumber(100, 2000);
  //     if (devID == 0)
  //       for (int i = 0; i < NUM_DEVICES; i++)
  //       {
  //         myPrefs.begin(deviceSpace[i], false);
  //         myPrefs.putUShort("speed", paramVal);
  //         myPrefs.end();
  //         myStepper[i].setSpeed(paramVal);
  //       }
  //     else
  //     {
  //       myPrefs.begin(deviceSpace[devID - 1], false);
  //       myPrefs.putUShort("speed", paramVal);
  //       myPrefs.end();
  //       myStepper[devID - 1].setSpeed(paramVal);
  //     }
  //     break;

  //   case 'T':
  //     BTSerial.println("\n Throw (steps, valid value 200 - 800, default = 600, 1000 steps = 7mm)");
  //     showCurrentValues('T');
  //     BTSerial.println("\n Enter 'C' to change or empty line  to exit");
  //     if (getUpperChar(millis()) != 'C')
  //       break;
  //     BTSerial.println(" Enter device (1 - 4) or 0 for all");

  //     devID = getNumber(0, 4);
  //     BTSerial.print(" Enter value for ");
  //     if (devID == 0)
  //       BTSerial.println("all devices");
  //     else
  //     {
  //       BTSerial.print("device ");
  //       BTSerial.println(devID);
  //     }
  //     paramVal = getNumber(200, 800);
  //     if (devID == 0)
  //       for (int i = 0; i < NUM_DEVICES; i++)
  //       {
  //         myPrefs.begin(deviceSpace[i], false);
  //         myPrefs.putUShort("throw", paramVal);
  //         myPrefs.end();
  //         myStepper[i].setStrokeSteps(paramVal);
  //       }
  //     else
  //     {
  //       myPrefs.begin(deviceSpace[devID - 1], false);
  //       myPrefs.putUShort("throw", paramVal);
  //       myPrefs.end();
  //       myStepper[devID - 1].setStrokeSteps(paramVal);
  //     }
  //     break;

  //   case 'F':
  //     BTSerial.println("\n Force (valid value 0 - 1500, default = 500)");
  //     BTSerial.println(" Larger values reduce force\n");
  //     showCurrentValues('F');
  //     BTSerial.println("\n Enter 'C' to change or empty line  to exit");
  //     if (getUpperChar(millis()) != 'C')
  //       break;
  //     BTSerial.println(" Enter device (1 - 4) or 0 for all");

  //     devID = getNumber(0, 4);
  //     BTSerial.print(" Enter value for ");
  //     if (devID == 0)
  //       BTSerial.println("all devices");
  //     else
  //     {
  //       BTSerial.print("device ");
  //       BTSerial.println(devID);
  //     }
  //     paramVal = getNumber(0, 1500);
  //     if (devID == 0)
  //       for (int i = 0; i < NUM_DEVICES; i++)
  //       {
  //         myPrefs.begin(deviceSpace[i], false);
  //         myPrefs.putUShort("force", paramVal);
  //         myPrefs.end();
  //         myStepper[i].setTorqueLimit(paramVal);
  //       }
  //     else
  //     {
  //       myPrefs.begin(deviceSpace[devID - 1], false);
  //       myPrefs.putUShort("force", paramVal);
  //       myPrefs.end();
  //       myStepper[devID - 1].setTorqueLimit(paramVal);
  //     }
  //     break;

  //   case 'D':
  //     BTSerial.println("\n Direction (0 or 1, 1 reverses the normal direction of throw\n");
  //     showCurrentValues('D');
  //     BTSerial.println("\n Enter 'C' to change or empty line  to exit");
  //     if (getUpperChar(millis()) != 'C')
  //       break;
  //     BTSerial.println(" Enter device (1 - 4) or 0 for all");

  //     devID = getNumber(0, 4);
  //     BTSerial.print(" Enter value for ");
  //     if (devID == 0)
  //       BTSerial.println("all devices");
  //     else
  //     {
  //       BTSerial.print("device ");
  //       BTSerial.println(devID);
  //     }
  //     paramBool = getNumber(0, 1);
  //     if (devID == 0)
  //       for (int i = 0; i < NUM_DEVICES; i++)
  //       {
  //         myPrefs.begin(deviceSpace[i], false);
  //         myPrefs.putBool("reversed", paramBool);
  //         myPrefs.end();
  //         myStepper[i].setReversed(paramBool);
  //       }
  //     else
  //     {
  //       myPrefs.begin(deviceSpace[devID - 1], false);
  //       myPrefs.putBool("reversed", paramBool);
  //       myPrefs.end();
  //       myStepper[devID - 1].setReversed(paramBool);
  //     }
  //     break;

  //   default:
  //     return;
  //   }
  // }
}
/*****************************************************************************/
// configures wifi SSID and password
void setCredentials()
{
  String myString;
  String wifiString;

  // BTSerial.print("\nEnter SSID: ");
  // while (!BTSerial.available())
  // {
  // }
  // myString = BTSerial.readString();
  // myString.trim();
  // if (myString.length() == 0)
  //   return;

  // wifiString = myString;
  // BTSerial.print("\nEnter WiFi password: ");
  // while (!BTSerial.available())
  // {
  // }
  // myString = BTSerial.readString();
  // myString.trim();
  // if (myString.length() == 0)
  //   return;

  // myPrefs.begin("general", false);
  // myPrefs.putString("SSID", wifiString);
  // BTSerial.print("SSID changed to ");
  // BTSerial.println(wifiString);
  // myPrefs.putString("wifipassword", myString);
  // myPrefs.end();
  // BTSerial.print("Password changed to ");
  // BTSerial.println(myString);
  // BTSerial.println("\nReboot is required");
  // return;
}

