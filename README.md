# Badtooth for ESP32
Badtooth is a badusb but using bluetooth

## Librairies
- [BleKeyboard](https://github.com/T-vK/ESP32-BLE-Keyboard)
- [Wifi (ESP32 Board)]([https://github.com/T-vK/ESP32-BLE-Keyboard](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi))
- WebServer (ESP32 Board)

## Material
- An esp32
- A computer

## Installation
1. Download the .ino file from the [last release](https://github.com/ri1ongithub/badtooth/releases).
2. Open it in the Arduino IDE.
3. In Tools > Partition Scheme, select "Minimal SPIFFS".
4. Plug your esp32 and upload BadTooth with the Upload button.

## Usage
1. Connect to the A.P with the ssid "BadTooth" and the password "YouShallNotPass".
2. Connect the victime's device to the bluetooth device "Bluetooth Keyboard".
3. Open "192.168.4.1" with your browser.

## Screenshots
![Web UI When no device is connected](https://github.com/ri1ongithub/badtooth/assets/49335122/51da56be-8fc3-4edc-aabf-8ec2cfe82f8c) ![Web UI When a device is connected](https://github.com/ri1ongithub/badtooth/assets/49335122/a4dfcd9f-604a-4f23-83fd-962f64c5fbf9)
