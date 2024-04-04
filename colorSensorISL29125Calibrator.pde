// Code that helps to calibrate the ISL29125 color sensor
// Risto Niemi 2024
// This code is used together with an Arduino software.
// You can use any Arduino board, which has I2C bus for the sensor.
//

import processing.serial.*;

Serial arduino; // Declare a Serial object

int x0 = 500;
int y0 = 400;
int red = 0;
int green = 0;
int blue = 0;



void setup() { 
    size(1000, 800);
    fill(0);
    
    arduino = new Serial(this, Serial.list()[1], 115200); // Connect to Arduino
    
    fill(0);
    circle(x0, y0, 600);       
}

void draw() {  
    if (arduino.available() > 0) {
        String data = arduino.readStringUntil('\n'); // Read data from Arduino
        if (data != null) {
            int[] values = int(split(data, ' '));
            print("Red = " + values[0] + "   ");
            print("Green = " + values[1] + "   ");
            println("Blue = " + values[2]);
                  
            red = values[0];
            green = values[1];
            blue = values[2];
            
            fill(red, green, blue);
            circle(x0, y0, 600);

        }
    }
}
