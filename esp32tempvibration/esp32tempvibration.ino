#include <OneWire.h>
#include <DallasTemperature.h>
#include <BluetoothSerial.h>

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

BluetoothSerial SerialBT;

const int motorPin = 12;  // Pin for the vibration motor

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");  // Set the Bluetooth name to "ESP32_BT"
  
  pinMode(motorPin, OUTPUT);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  if (SerialBT.available()) {
    char command = SerialBT.read();
    if (command == '1') {
      digitalWrite(motorPin, HIGH);
      SerialBT.println("Motor Turned On");
    } else if (command == '0') {
      digitalWrite(motorPin, LOW);
      SerialBT.println("Motor Turned Off");
    }
  }

  // Send temperature data over Bluetooth
  SerialBT.print("Temperature: ");
  SerialBT.print(temperature);
  SerialBT.println(" °C");
  
  delay(1000);
}
