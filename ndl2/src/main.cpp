/* Switching boxes */
 
// Librarys that the IoT Matrix uses
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <WEMOS_Matrix_GFX.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>
 
MLED matrix(7); //set intensity=7 (maximum)
 
void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
}

void line_spin() {
  matrix.clear();
  for (int i = 0; i < 7; i++) {
    matrix.clear();
    matrix.drawLine(0, i, 7, 7-i, 1);
    matrix.writeDisplay();
    delay(100);
  }
  for (int i = 7; i > 0; i--) {
    matrix.clear();
    matrix.drawLine(i, 0, 7-i, 7, 1);
    matrix.writeDisplay();
    delay(100);
  }
}

void loop() {
  line_spin();

}

 
void loop2() {
  matrix.clear(); // Clear the matrix field
  matrix.drawRect(0,0, 8,8, LED_ON); // Draws a empty square with positions y = 0, x = 0, y length = 8, x length = 8 and telling the leds to be on.
  matrix.fillRect(2,2, 4,4, LED_ON); // Draws a filled square from positions y = 2, x = 2, y length = 4, x length = 4 and telling the leds to turn on
  matrix.writeDisplay();  // Write the changes we just made to the display
  delay(500); // Wait for half a second
  matrix.drawRect(0,0,8,8, LED_OFF); // Turn the leds off
  matrix.drawRect(1,1, 6,6, LED_ON);
  matrix.fillRect(2,2,4,4, LED_OFF);
  matrix.writeDisplay();
  delay(500);
}