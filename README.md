# 🌡 ESP32 Temperature & Humidity Alert (Gmail)

This project reads temperature and humidity from a DHT11 sensor using an ESP32, and sends the readings to an email address via Gmail SMTP.

---

## 🔧 Components

- ESP32 development board
- DHT11 sensor
- Jumper wires
- Breadboard (optional)

---

## ⚙ Wiring Diagram

| DHT11 Pin | ESP32 GPIO |
|-----------|------------|
| VCC       | 3.3V       |
| GND       | GND        |
| DATA      | GPIO 26    |

![Circuit Diagram](https://github.com/Palash-theCoder2005/ESP32_Email_Alert/commit/fb22062fe8272de65d48ec783cd2019b7092145d) 

---

## 🔌 Arduino Setup

### Install Libraries:
- [ESP Mail Client](https://github.com/mobizt/ESP-Mail-Client)
- DHT sensor library (Adafruit)
- WiFi.h (built-in)

### Board and Port Select
  - 

### Gmail Setup:
1. Enable *2-Step Verification* in your Google Account.
2. Generate a *16-digit App Password* at [Google App Passwords](https://myaccount.google.com/apppasswords)
3. Use that password in the code.

---

## 📩 Email Format Example
 Subject: Sensor Alert
🌡 Temp: 28.5°C 💧 Humidity: 63.0%


Good Luck
