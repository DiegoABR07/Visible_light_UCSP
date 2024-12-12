/*
  test_tx.ino: VLC transmitter
  Course: CESE4110 Visible Light Communication & Sensing
*/

const int ledR = 8;  // GPIO for controlling R channel (Red)
const int ledG = 9;  // GPIO for controlling G channel (Green)
const int ledB = 10; // GPIO for controlling B channel (Blue)

int sequence[] = {0, 0, 1, 0, 1, 0, 1, 1};  // Example binary sequence
int sequenceLength = sizeof(sequence) / sizeof(sequence[0]);  // Calculate the length of the sequence

float Freq = 1000;  // Transmission frequency in Hz (1000 Hz = 1 ms per bit)
float del;

/*
 * Setup configurations
 */
void setup() {
  Serial.begin(115200);  // Set baud rate for serial communication

  // Set LED pins as output
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  // Initialize all LEDs to OFF state
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
}

/*
 * The main function to transmit the sequence
 */
void loop() {
  // Iterate through the binary sequence and transmit each bit
  for (int i = 0; i < sequenceLength; i++) {
    if (sequence[i] == 1) {
      digitalWrite(ledR, HIGH);  // Turn ON Red LED to represent '1'
    } else {
      digitalWrite(ledR, LOW);   // Turn OFF Red LED to represent '0'
    }

    // Print the current bit to the Serial Monitor
    Serial.println(sequence[i]);

    // Calculate delay based on the transmission frequency
    del = 1000.0 / Freq;  // Time period for each bit in milliseconds
    delay(del);           // Wait for the calculated time in milliseconds
  }

  // Optional: Add a pause before repeating the sequence
  // delay(1000);  // Wait 1 second before repeating the message
}
