# 📱 Blynk Setup Guide

**Project:** Line Fault Detection System (ESP32 IoT)

---

## 🔧 Step 1: Create Template

1. Open **Blynk IoT app / web dashboard**
2. Create a new **Template**
3. Set:

   * Hardware: **ESP32**
   * Connection Type: **WiFi**

---

## 📡 Step 2: Create Datastreams

Create the following **Virtual Pins**:

| Name          | Virtual Pin | Data Type | Description           |
| ------------- | ----------- | --------- | --------------------- |
| Relay Control | V0          | Integer   | Manual ON/OFF control |
| Voltage       | V1          | Double    | Bus voltage (V)       |
| Current       | V2          | Double    | Current (mA)          |
| Power         | V3          | Double    | Power (mW)            |
| LDR State     | V4          | Integer   | Light/Dark detection  |
| Latitude      | V5          | Double    | GPS latitude          |
| Longitude     | V6          | Double    | GPS longitude         |
| Mode          | V7          | Integer   | Auto / Manual mode    |

---

## 🎛️ Step 3: Dashboard Widgets

Add these widgets:

### 🔘 Controls

* **Button Widget**

  * Datastream: V0
  * Mode: Switch
  * Label: Relay Control

* **Switch Widget**

  * Datastream: V7
  * Label: Auto Mode

---

### 📊 Monitoring

* **Gauge / Display**

  * V1 → Voltage
  * V2 → Current
  * V3 → Power

* **LED Widget**

  * V4 → LDR State
  * (ON = Dark, OFF = Light)

---

### 🗺️ GPS Tracking

* **Map Widget**

  * Latitude: V5
  * Longitude: V6

---

## ⚙️ Step 4: Get Credentials

From template/device info copy:

* `BLYNK_TEMPLATE_ID`
* `BLYNK_DEVICE_NAME`
* `BLYNK_AUTH_TOKEN`

Paste into your `config.h`:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "Line Fault Detection"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
```

---

## 🔔 Optional (Recommended)

### Notifications (Fault Alert)

Add **Event / Notification**:

* Trigger when:

  * Current exceeds threshold
* Message:

  ```
  ⚠️ Line Fault Detected!
  ```

---

## ✅ Final Checklist

* WiFi credentials added ✔
* Auth token added ✔
* Datastreams created ✔
* Widgets configured ✔
* ESP32 connected ✔

---

## 🚀 Result

You will get:

* Live energy monitoring
* GPS-based fault location
* Remote relay control
* Automatic fault response

---
