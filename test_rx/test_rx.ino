#define PD A0 // Photodiode pin
#define THRESHOLD 400 // Threshold for detecting 0 or 1

float txFreq = 1000;
float Freq = 2.5 * txFreq;  // Sampling frequency
float del;

void setup() {
  Serial.begin(115200);  // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(PD);

  // Print the sensor value for debugging or further processing
  Serial.println(sensorValue);

  // Check if sensor value is above or below the threshold
  /*
  if (sensorValue > THRESHOLD) {
    Serial.println("1");
  } else {
    Serial.println("0");
  }
  */

  // Delay for next sample at 2000 Hz
  del = 1000 / Freq;
  delay(del); 
}
