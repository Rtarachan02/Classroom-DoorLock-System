#define BLYNK_TEMPLATE_ID "TMPL3T_wV7wcs"
#define BLYNK_TEMPLATE_NAME "Classroom DoorLock"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <HTTPClient.h>  // Needed for ThingSpeak

// WiFi & Blynk Credentials
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
char auth[] = "rpkkI5CXG6nLgdFXyGKeptVwfEc1JLlH";

// ThingSpeak Settings
String apiKey = "AEYYDU3LAJ87PEX6";
String server = "http://api.thingspeak.com/update";

Servo doorLock; // Servo object
bool isLocked = true;

#define BLYNK_UNLOCK V1
#define BLYNK_LOCK V2
#define BLYNK_STATUS V3
#define BLYNK_PIR V4  // PIR Sensor Virtual Pin

#define PIR_SENSOR 27  // PIR Sensor GPIO Pin
bool motionDetected = false;

void sendToThingSpeak(bool lockStatus, bool motion) {
  HTTPClient http;
  String url = server + "?api_key=" + apiKey +
               "&field1=" + (lockStatus ? "1" : "0") +
               "&field2=" + (motion ? "1" : "0");  // Sending PIR status too

  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    Serial.println("✅ Data Sent to ThingSpeak!");
  } else {
    Serial.println("❌ ThingSpeak Error: " + String(http.errorToString(httpCode).c_str()));
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  pinMode(PIR_SENSOR, INPUT);  // Set PIR sensor pin as input

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");

  Blynk.begin(auth, ssid, pass);
  
  doorLock.attach(13);  // Attach servo to GPIO 13
  doorLock.write(90);   // Start in locked position
  Serial.println("🔒 System Ready: Door Locked");
  
  sendToThingSpeak(isLocked, motionDetected);
  Blynk.virtualWrite(BLYNK_STATUS, isLocked ? "Locked" : "Unlocked");
  Blynk.virtualWrite(BLYNK_PIR, motionDetected ? 1 : 0);
}

// Blynk Virtual Buttons
BLYNK_WRITE(BLYNK_UNLOCK) {
  isLocked = false;
  doorLock.write(0);  // Unlock
  Serial.println("🔓 Door Unlocked via Blynk");

  sendToThingSpeak(isLocked, motionDetected);
  Blynk.virtualWrite(BLYNK_STATUS, isLocked ? "Locked" : "Unlocked");
}

BLYNK_WRITE(BLYNK_LOCK) {
  isLocked = true;
  doorLock.write(90);  // Lock
  Serial.println("🔒 Door Locked via Blynk");

  sendToThingSpeak(isLocked, motionDetected);
  Blynk.virtualWrite(BLYNK_STATUS, isLocked ? "Locked" : "Unlocked");
}

// PIR Sensor Motion Detection
void loop() {
  Blynk.run();

  int pirValue = digitalRead(PIR_SENSOR);
  if (pirValue == HIGH && !motionDetected) {
    motionDetected = true;
    Serial.println("🚶 Motion Detected! Unlocking door...");
    
    isLocked = false;
    doorLock.write(0);  // Unlock the door
    sendToThingSpeak(isLocked, motionDetected);
    
    Blynk.virtualWrite(BLYNK_STATUS, "Unlocked");
    Blynk.virtualWrite(BLYNK_PIR, 1);
  } 
  else if (pirValue == LOW && motionDetected) {
    motionDetected = false;
    Serial.println("🏠 No Motion Detected.");
    
    Blynk.virtualWrite(BLYNK_PIR, 0);
  }
}

// Blynk Read Function (Request from App)
BLYNK_READ(BLYNK_STATUS) {
  Blynk.virtualWrite(BLYNK_STATUS, isLocked ? "Locked" : "Unlocked");
}

BLYNK_READ(BLYNK_PIR) {
  Blynk.virtualWrite(BLYNK_PIR, motionDetected ? 1 : 0);
}
