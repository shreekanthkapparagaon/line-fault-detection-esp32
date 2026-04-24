#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <Adafruit_INA219.h>
#include "config.h"

// -------- Objects --------
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
Adafruit_INA219 ina219;
BlynkTimer timer;

// -------- Pins --------
#define GPS_RX      16
#define GPS_TX      17
#define RELAY_PIN   26
#define LDR_PIN     32

// -------- Variables --------
bool relayState = false;
bool autoMode = true;

// -------- Blynk Controls --------
BLYNK_WRITE(V0) {
    relayState = param.asInt();
    if (!autoMode) {
        digitalWrite(RELAY_PIN, relayState ? LOW : HIGH);
    }
}

BLYNK_WRITE(V7) {
    autoMode = param.asInt();
}

// -------- Sensor Task --------
void sendData() {

    int lightState = digitalRead(LDR_PIN);

    // Auto mode logic
    if (autoMode) {
        if (lightState == LOW) {
            digitalWrite(RELAY_PIN, LOW);
            relayState = 1;
        } else {
            digitalWrite(RELAY_PIN, HIGH);
            relayState = 0;
        }
    }

    float voltage = ina219.getBusVoltage_V();
    float current = ina219.getCurrent_mA();
    float power   = ina219.getPower_mW();

    while (gpsSerial.available()) {
        gps.encode(gpsSerial.read());
    }

    // Send to Blynk
    Blynk.virtualWrite(V1, voltage);
    Blynk.virtualWrite(V2, current);
    Blynk.virtualWrite(V3, power);
    Blynk.virtualWrite(V4, lightState);
    Blynk.virtualWrite(V0, relayState);

    if (gps.location.isValid()) {
        Blynk.virtualWrite(V5, gps.location.lat());
        Blynk.virtualWrite(V6, gps.location.lng());
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);

    digitalWrite(RELAY_PIN, HIGH);

    gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
    Wire.begin(21, 22);

    ina219.begin();

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

    timer.setInterval(2000L, sendData);
}

void loop() {
    Blynk.run();
    timer.run();
}