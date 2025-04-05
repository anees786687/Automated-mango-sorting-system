#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

const int readPin = 8; // Define the pin number to read

void setup() {
  pinMode(readPin, INPUT);

  Serial.begin(9600);
  while (!Serial) delay(10); // wait bro

  // sensor init
  if (!amg.begin()) {
    Serial.println("Could not find a valid AMG8833 sensor, check wiring!");
    while (1); // Halt if sensor initialization fails
  }

  
  // amg.setMode(AMG88xx_NORMAL_MODE); // Adjust rate if needed
}

void loop() {
  // read temp
  int value = digitalRead(readPin);
  float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
  amg.readPixels(pixels);

  
  int avg = 0;
  for (int i = 18; i <= 42; i += 8) {
    for (int j = 0; j <= 3; j++) {
      avg += pixels[i + j];
    }
  } // taking mean of the values around the center of sensing matrix
  avg /= 16; // average it

  
  String data = "T:"; // send to Rpi
  data += "\n"; // add newline for clear termination
  if (value == HIGH) Serial.print(data);
  delay(2000); // 
}
