#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <ESP_Mail_Client.h>

/* Wi-Fi and email credentials */
#define WIFI_SSID "your_ssid"
#define WIFI_PASSWORD "your_pwd"
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "yours_mail@gmail.com"
#define AUTHOR_PASSWORD "email_password"
#define RECIPIENT_EMAIL "recipients_mail@gmail.com"



/* Initialize ultrasonic sensor pins */
int trigPin1 = D3;
int echoPin1 = D4;
int trigPin2 = D1;
int echoPin2 = D2;

int Chocolate = 0;
int Icecream = 0;

/* Declare the global SMTPSession object */
SMTPSession smtp;

/* Callback function to monitor the status of email sending */
void smtpCallback(SMTP_Status status);

void setup() {
  Serial.begin(9600);  // Set baud rate to 9600
  delay(100);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to Wi-Fi.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Configure pins for ultrasonic sensors
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Enable debug mode and set callback
  smtp.debug(1);
  smtp.callback(smtpCallback);
}

void loop() {
  Product1();
  Product2();

  // Check if email notification is needed
  if (Icecream == 0 || Chocolate == 0) {
    sendEmailNotification();
    delay(60000); // Wait 1 minute before sending another notification
  }

  delay(1000); // Delay for sensor readings
}

/* Function for Product 1: Icecream stock */
void Product1() {
  int duration, distance;
  
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance < 23) { Icecream = 5; }
  else if (distance >= 23 && distance < 35) { Icecream = 4; }
  else if (distance >= 35 && distance < 47) { Icecream = 3; }
  else if (distance >= 47 && distance < 60) { Icecream = 2; }
  else if (distance >= 60 && distance < 70) { Icecream = 1; }
  else { Icecream = 0; }

  Serial.print("Icecream stock: ");
  Serial.println(Icecream);
}

/* Function for Product 2: Chocolate stock */
void Product2() {
  int duration, distance;
  
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance < 23) { Chocolate = 5; }
  else if (distance >= 23 && distance < 35) { Chocolate = 4; }
  else if (distance >= 35 && distance < 47) { Chocolate = 3; }
  else if (distance >= 47 && distance < 60) { Chocolate = 2; }
  else if (distance >= 60 && distance < 70) { Chocolate = 1; }
  else { Chocolate = 0; }

  Serial.print("Chocolate stock: ");
  Serial.println(Chocolate);
}

/* Function to send email notification */
void sendEmailNotification() {
  // Configure SMTP session
  Session_Config config;
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;

  // Create email message
  SMTP_Message message;
  message.sender.name = "Inventory Alert System";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Inventory Alert: Stock Out!";
  message.addRecipient("Admin", RECIPIENT_EMAIL);

  String emailContent = "Alert: Inventory is low.\n";
  if (Icecream == 0) emailContent += "Icecream stock is out.\n";
  if (Chocolate == 0) emailContent += "Chocolate stock is out.\n";
  message.text.content = emailContent.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  // Send email
  if (!smtp.connect(&config)) {
    Serial.println("Error connecting to SMTP server.");
  } else {
    if (MailClient.sendMail(&smtp, &message)) {
      Serial.println("Email sent successfully.");
    } else {
      Serial.printf("Error sending email: %s\n", smtp.errorReason().c_str());
    }
    smtp.closeSession();
  }
}

/* SMTP status callback function */
void smtpCallback(SMTP_Status status) {
  Serial.println(status.info());
  if (status.success()) {
    Serial.printf("Message sent successfully: %d\n", status.completedCount());
  } else {
    Serial.printf("Failed message count: %d\n", status.failedCount());
  }
}