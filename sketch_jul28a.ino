#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "Wifi name ";
const char* password = "wifi password";

// Gmail SMTP credentials
#define AUTHOR_EMAIL "senderemail@gmail.com"
#define AUTHOR_PASSWORD "16 digit app password from Google"  // 16-digit App Password

// Recipient email (you can later replace with Airtel SMS if it works)
#define RECIPIENT_EMAIL "recipientemail@gmail.com"

// DHT11 sensor setup
#define DHTPIN 26
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// SMTP setup
SMTPSession smtp;
ESP_Mail_Session session;
SMTP_Message message;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("📶 Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected");

  dht.begin();

  // SMTP server settings
  session.server.host_name = "smtp.gmail.com";
  session.server.port = 465;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";
  session.time.ntp_server = "pool.ntp.org";

  smtp.debug(1);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("❌ Failed to read from DHT11 sensor");
    delay(10000);  // Wait 10 seconds before retry
    return;
  }

  // Prepare email message
  message.sender.name = "ESP32 Sensor";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Sensor Alert";
  message.clearRecipients();
  message.addRecipient("Palash", RECIPIENT_EMAIL);

  String msgText = "🌡 Temp: " + String(temp) + " °C\n";
  msgText += "💧 Humidity: " + String(hum) + " %";
  message.text.content = msgText.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  // Connect to SMTP
  if (!smtp.connect(&session)) {
    Serial.println("❌ SMTP connection failed");
  } else {
    if (MailClient.sendMail(&smtp, &message)) {
      Serial.println("✅ Message sent successfully");
    } else {
      Serial.println("❌ Failed to send: " + smtp.errorReason());
    }
    smtp.closeSession();
  }

  // Wait 5 minutes (300000 ms)
  Serial.println("⏱ Waiting 5 minutes...");
  delay(300000);
}