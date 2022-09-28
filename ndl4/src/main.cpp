 // Includes global variables and librarys that the OLED display and buzzer uses
#include <Arduino.h>
#include <ittiot.h>
#include <Ticker.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#include <Buzzer.h>


#define WIFI_NAME "TalTech"
#define WIFI_PASSWORD ""
#define MQTT_SERVER "193.40.245.72"
#define MQTT_PORT "1883"
#define MQTT_USER "test"
#define MQTT_PASS "test"

 
// Change it according to the real name of the PIR node
#define PIR_TOPIC "ESP16/pir"

 
//Pin definition for buzzer
#define BUZZER_PIN D8
Buzzer buzzer(BUZZER_PIN);


bool buzz = false;
// It will print out anything it receives on "security" topic.
// If the message it receives is "Motion detected!". It will activate the buzzer for 1 second.
void iot_received(String topic, String msg)
{ 
  Serial.println("Received: " + topic + " - " + msg);
  if(msg=="1") //sound the buzzer, if motion has been detected
  {
    // analogWrite(BUZZER_PIN, 512); // setting buzzer output to some value
    // buzzer.sound(100,1000);
    buzz = true;
  }
  else if (msg == "0")
  {
    // analogWrite(BUZZER_PIN, 0); // switching the busser off
    // digitalWrite(BUZZER_PIN, LOW);
    buzz = false;
  }
  
}
 
// Function started after the connection to the server is established.
void iot_connected()
{
  // Send message to serial port to show that connection is established
  Serial.println("MQTT connected callback");
  // Send message to MQTT server to show that connection is established
  iot.log("IoT Home security example!");
  // Subscribe to get security messages
  iot.subscribe(PIR_TOPIC);
}
 
void setup()
{
  // Initialize serial port and send message
  Serial.begin(115200); // setting up serial connection parameter
  Serial.println("Booting");
 
  iot.setConfig("wname", WIFI_NAME);
  iot.setConfig("wpass", WIFI_PASSWORD);
  iot.setConfig("msrv", MQTT_SERVER);
  iot.setConfig("mport", MQTT_PORT);
  
  iot.printConfig();  // print IoT json config to serial
  iot.setup();// Initialize IoT library
 
  // Initialize buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

int time_on = 0;

bool buzz_last = false;
int c_time = 0;
void loop()
{
  int c_time = 0;
  if (buzz != buzz_last and !buzz_last)
  {
    c_time = millis();
    buzz_last = buzz;
  }
  if (buzz != buzz_last and buzz_last)
  {
    time_on += millis() - c_time;
    c_time = millis();
    buzz_last = buzz;
  }
  iot.handle(); // IoT behind the plan work, it should be periodically called
  delay(200); // Wait for 0.2 second
  if (buzz) {
    buzzer.sound(100, 200);
  }

  String msg = String(time_on);
  Serial.println(msg);
  iot.publishMsg("time_on", msg.c_str());
}