# ERSS
Emergency Response Support System
ESP32 based hardware device detects accidents and notify (using BLE) nearst mobile devices listening to its advertising.
Android application listen to BLE broadcast message from this device. When it finds any active device broadcasting emergency message the app sends message (containing user provided information and the location of accidents) to ERSS Team and to the emergency contacts added by the user.
