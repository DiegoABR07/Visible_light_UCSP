import serial
import csv
import time

# Constants
SERIAL_PORT = 'COM8'  # Set to the Arduino Port
BAUD_RATE = 115200
RECORD_TIME = 10  # Time in seconds to record data

# Initialize serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Initialize empty list to store sensor data and thresholds
sensorValue_data = []
threshold_data = []

# Create a function to read and process data from Arduino
def read_and_process_data():
    try:
        # Read from the serial port and decode safely
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        
        # Parse the line to extract sensorValue and threshold
        if line.startswith("Sensor_Value:"):
            data = line.split(",")  # Split the string by comma
            sensorValue_str = data[0].split(":")[1]
            threshold_str = data[1].split(":")[1]

            sensorValue = int(sensorValue_str)
            threshold = int(threshold_str)

            sensorValue_data.append(sensorValue)
            threshold_data.append(threshold)

            # Print sensor value and threshold for monitoring
            print(f'Sensor: {sensorValue}, Threshold: {threshold}')
    except Exception as e:
        # Catch any exceptions during data processing
        print(f"Error reading line: {e}")

# Function to save sensor data and thresholds to CSV
def save_data_to_csv():
    print(f"Saving {len(sensorValue_data)} records to CSV...")  # Log message for verification
    with open('arduino_sensor_data.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Sensor Value', 'Threshold'])
        for sensor, threshold in zip(sensorValue_data, threshold_data):
            writer.writerow([sensor, threshold])
    print("Data saved to arduino_sensor_data.csv")

# Start recording sensor data for 5 seconds
start_time = time.time()

while True:
    read_and_process_data()
    ##time.sleep(0.1)  # Add a small delay to avoid overwhelming the serial buffer
    if time.time() - start_time >= RECORD_TIME:
        break

# Save the recorded data to CSV
save_data_to_csv()

# Close the serial connection
ser.close()
print("Serial connection closed.")
