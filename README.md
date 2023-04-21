# MQTo
## What's new
MQTO is a redo of MQTTtosT redesigned to eliminate the Bluetooth connection. All configuration is now accomplished using the builtin web server. Additional functionality includes automatic wifi provisioning and OTA code and data uploading.

## Description
This software provides a means to control track switches (turnouts) on a model railroad. It should be used in conjunction with JMRI software and an MQTT server although the system will work standalone. The software runs on an ESP32 30 pin devkit device.

The ESP32 device will control four micro stepper motors through four motor driver boards mounted on the mother board. The micro stepper actuators are extremely small, on the order of 3/4" square with a height of less than 1/4". They can be placed on the surface of the layout, under the turnout throw bar, and hidden with scenery materials. They will self adjust for throw in this application. 

Four inputs are provided to allow local control of the motors using push button switches. Actuating these switches will toggle the position of the turnout.

An output to drive a string of four neoPixel LED devices is provided. These LEDs will display locally the status of each of the turnouts. The colors are red for thrown, green for closed and flashing yellow while in transition. The LEDs will display blue on startup until initialized. A neoPixel strip may be used by cutting the strip to a length of four LEDs. A good choice is a meter long strip of 60 LEDs. These will be spaced about 5/8" apart and can be installed on the fascia as a group. Or they can be cut apart and installed individually. If cut apart they must be connected as they were in the strip, namely the power, ground and data lines must be connected between devices. Turnout 1 will be indicated by the first LED in the string, then 2, 3 and 4.

Primary control of the turnout motors is by using MQTT over WiFi. The source of commands is expected to be JMRI software, however other MQTT capable sources may be used, such as an app on a cell phone or a tablet. An MQTT server must be setup on the network. The mosquitto version of this server is recommended. It can run on a small computer such as a Raspberry Pi.

The software will send turnout status data back to JMRI at the end of each commanded movement. It will also send UNKNOWN status while the transition is in progress.

A gerber file for the required motherboard PCB is included in this distribution. I can be sent as is to a PCB fabrication shop such as JLCPCB.

## Important considerations

This software was developed using VSCode and PlatformIO with 'ESP32 Dev Module' board configuration. Initially it will fail to load into the host because of lack of memory. This is alleviated by modifying the partition scheme. Access that setting from the Arduino Tools menu. Select some scheme that does not use OTA (Over the Air software loading). Choosing this reduced the size from 101% of memory to 42%.

On first start the code will attemp to connect to the default WiFi SSID and will fail. TBD all this

The left hand part of the MQTT topic set in the device must match the corresponding setting in JMRI. The default in JMRI is "/trains/track/turnout/". The leading slash is incorrect, remove it in JMRI. The default topic left hand part in the device is "trains/track/turnout/. This string can be changed using the menu, but it must match the equivalent string in JMRI. The default feedback topic left hand part is "trains/track/sensor/turnout/".

The complete topic sent to the node must be of the form "\<left hand topic\>\<node name\>/\<device name\>". The node name and device names (4) are configurable from the menu. The complete topic sent from the device to indicate turnout position will be of the form "\<feedback topic left hand part\>/\<node name\>/\<device name\>".

## Usage
The software can be loaded onto an ESP32 device using a download tool available from EspressIF (https://www.espressif.com/en/support/download/other-tools).

The software is configured using any web browser. The software creates a web server on the ESP32 device. To access the configuration pages the ip address of the device must be known and entered as the URL in the browser. The configuration menu has individual pages for mqtt setup, stepper parameters and over-the-air (OTA) updates of the program firmware and for web page updates.

Meaningful device names should be configured from the menu. The default device name for all 4 devices is "noname". The names must be unique for proper operation.

The stepper motor characteristics may need to be modified from the default values. These include the speed, throw, force and direction. The throw parameter should be set such that the throw is just slightly greater than the amount required to move the points from one stock rail to the other. The force parameter allows for reduction of the force that is exerted. This works by terminating current flow in the motor windings prior to the end of the normal step. The amount is in percent of full force and a value of 75 to 100 has been shown to be effective. Without a reduction the motor may produce enough force to break something. The direction parameter is used to reverse the direction of throw if required to match the physical thrown position to the throw command.

## Versioning
Any change that affects operation increase the version number most significant digit. Any change that corrects an error will increase the version number middle digit. A change that does neither such as correcting a typo will increase the least significant digit.

## Sources
Possible sources for hardware...

ESP32 dev board: https://www.amazon.com/gp/product/B08NW6YZ8W/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&th=1

Motor driver board: https://www.amazon.com/gp/product/B08RMWTDLM/ref=ppx_yo_dt_b_asin_title_o01_s01?ie=UTF8&psc=1

Terminal blocks: https://www.amazon.com/dp/B07B791NMQ?psc=1&ref=ppx_yo2ov_dt_b_product_details

neoPixel strip: https://www.amazon.com/dp/B01MG49QKD?psc=1&ref=ppx_yo2ov_dt_b_product_details

Pin headers: https://www.amazon.com/dp/B07VP63Z78?psc=1&ref=ppx_yo2ov_dt_b_product_details

Micro steppers: eBay item 122072149870
