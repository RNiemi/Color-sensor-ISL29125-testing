Color sensor ISL29125 calibration and testing using Arduino Nano and Processing. The project is shown on a Youtube video with the name: Color sensor ISL29125 calibration and testing.
The .pde file is running in the PC, in the Processing application. The .ino file is running on the Arduino board.
During the calibration, only the Arduino is used. The RGB values from the Arduino can be seen on the Serial Monitor on the PC screen. The code on the Arduino board must be in calibration mode. This can be done by uncommenting the //calibration();
line.
When testing the sensor, the detected color can be seen when the Prcessing code (.pde file) is running on the PC. The Arduino code must be put to readColor mode.
