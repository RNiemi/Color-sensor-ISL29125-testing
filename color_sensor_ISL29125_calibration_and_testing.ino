/* Color sensor ISL29125 calibration and testing
  Risto Niemi 2024

What you need (at least):
1. Arduino Uno, or Nano, or Mega  
2. Color sensor ISL29125
  * Do not connect directly to the I2C bus of the Arduino board. Use a logic
      level shifter, because the sensor is using 3.3V logic.
3. Display (optional, because the RGB-values go to PC via serial connection):
   2x16 LCD display. I used Crowtail I2C LCD V2.0
        https://www.elecrow.com/wiki/index.php?title=Crowtail-_I2C_LCD

*/

#include <Wire.h>
#include "SparkFunISL29125.h"

// Declare sensor object
SFE_ISL29125 RGB_sensor;

// Calibration values:
// The values depend mostly on the lighting conditions.
// A calibration tutorial is in this YouTube video:
// https://www.youtube.com/watch?v=MwdANEcTiPY&t=756s
// The video is made by DroneBot Workshop

unsigned int redlow = 11;       // Use your own values here.
unsigned int greenlow = 15;     // You can get them by
unsigned int bluelow = 12;      // calibrating the sensor.

unsigned int redhigh = 200;     // same as above
unsigned int greenhigh = 274;
unsigned int bluehigh = 278;

 
// Declare RGB Values
int redVal = 0;
int greenVal = 0;
int blueVal = 0;

// The next rows are for the display initialisation.
// You don't need them if you do not connect a display to your Arduino board.
#include "LiquidCrystal.h"  //It is important to remove <LiquidCrystal_I2C.h> 
                            //library from the Arduino libraries folder!

// Connect via I2C, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);
int col = 16;
int row = 2;


void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Initialize the ISL29125 so it starts sampling
  if (RGB_sensor.init())
  {
    // Comment these 6 lines if no LCD display is used.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initialisation");
    lcd.setCursor(0, 1);
    lcd.print("successfull");
    delay(2000);
  }  
}


// The main program
void loop() {

  // Calibration can be activated by uncommenting the next line.   
  //calibration(); 

  // This subprogram reads rgb-values and sends them to the PC (or laptop).
  // If you are doing the calibration, comment the next line.
  readColor(); 
  
  // If you don't have an LCD-display. you can comment the following line.
  //print_to_lcd();  // Now it is commented, because I didn't have
                     // a display on this viedeo.
}


void readColor() {  

  // Read sensor values (16 bit integers)
  unsigned int red = RGB_sensor.readRed();
  unsigned int green = RGB_sensor.readGreen();
  unsigned int blue = RGB_sensor.readBlue();

  // Convert to RGB values
  int redV = map(red, redlow, redhigh, 0, 255);
  int greenV = map(green, greenlow, greenhigh, 0, 255);
  int blueV = map(blue, bluelow, bluehigh, 0, 255);
  
  // Constrain to values of 0-255
  redVal = constrain(redV, 0, 255);
  greenVal = constrain(greenV, 0, 255);
  blueVal = constrain(blueV, 0, 255);
       
  // Print out readings
  //Serial.print("Red: "); 
  Serial.print(redVal);
  Serial.print(" ");
  //Serial.print(" - Green: ");
  Serial.print(greenVal);
  Serial.print(" ");
  //Serial.print(" - Blue: "); 
  Serial.print(blueVal);
  Serial.print(" ");
  //Serial.print(" - Blue: "); 
  Serial.print(blueVal);
  Serial.print("\n");
  
  delay(2000);
}

void calibration() {
  // Reads 10 color samples and sends them to the serial monitor.
  for (int i = 0; i < 10; i++) {
    // Read sensor values (16 bit integers)
    unsigned int redC = RGB_sensor.readRed();
    unsigned int greenC = RGB_sensor.readGreen();
    unsigned int blueC = RGB_sensor.readBlue();
    
    Serial.print("RedC: "); 
    Serial.print(redC);
    Serial.print(" - GreenC: ");
    Serial.print(greenC);
    Serial.print(" - BlueC: "); 
    Serial.println(blueC);

    delay(2000);
  }
  Serial.println("The next 10 values will start coming in 10 seconds.");
  delay(10000);
}

void print_to_lcd() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R: ");
  lcd.print(redVal);
  lcd.print("   G: ");
  lcd.print(greenVal);
  lcd.setCursor(0, 1);
  lcd.print("B: ");
  lcd.print(blueVal);
}