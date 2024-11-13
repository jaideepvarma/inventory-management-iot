#  IoT-Based Inventory Monitoring System

## Overview

This IoT-based inventory monitoring system tracks stock levels of two products (Ice Cream and Chocolate) using ultrasonic sensors. When stock levels reach a critical low (0), the system automatically sends an email notification to alert the administrator to restock.

## Components

  - **NodeMCU ESP8266:** Microcontroller used to process sensor data and communicate over Wi-Fi.
  - **Ultrasonic Sensors:** Measure distance to calculate stock levels.
  - **Breadboard:** Organizes components and connections.
  - **Jumper Wires:** Connect components.

## Functional Overview

- **Stock Monitoring:**
  - Each product's stock level is monitored by an ultrasonic sensor that calculates the distance to determine stock status.
  - Stock levels range from 5 (full) to 0 (empty) based on distance thresholds.
- **Email Notifications:**
  - When either product’s stock level reaches 0, the system automatically sends an email alert to a specified recipient using SMTP.
  - To avoid spamming, the system waits 1 minute before sending additional notifications.


## Setup and Configuration

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/iot-inventory-management
   ```
2. **Navigate to the project directory:**
   ```bash
   cd iot-inventory-management
   ```
3. **Configure Wi-Fi and Email Settings:**
     - Open the main code file and update the following details with your credentials:
     ```bash
     #define WIFI_SSID "your_ssid"
     #define WIFI_PASSWORD "your_pwd"
     #define AUTHOR_EMAIL "your_email@gmail.com"
     #define AUTHOR_PASSWORD "your_email_password"
     #define RECIPIENT_EMAIL "recipient_email@gmail.com"
     ```


5. **Install Required Libraries:**
   - Install the necessary Arduino libraries:
      - ESP_Mail_Client for email functionality.
      - WiFi for ESP32 or ESP8266WiFi for ESP8266.
   - Install libraries using the Arduino Library Manager.

6. **Upload Code:**
   - Connect your ESP8266 to your computer and upload the code via the Arduino IDE.

## Usage

   - Power on the NodeMCU and wait for it to connect to Wi-Fi.
   - The system will begin monitoring stock levels and printing information to the Serial Monitor.
   - Stock levels will be displayed in real time.
   - When either Ice Cream or Chocolate stock reaches 0, an email alert will be sent to the specified recipient.



## Code Explaination

  - Wi-Fi Connection Setup: Connects to the specified Wi-Fi network to enable communication.
  - Ultrasonic Sensor Setup and Monitoring: Calculates stock levels for Ice Cream and Chocolate based on predefined distance thresholds.
  - Email Notification System: Sends an email alert when stock levels reach 0, using SMTP for email delivery.
  - Loop Function: Continuously monitors stock levels and triggers email notifications as needed.