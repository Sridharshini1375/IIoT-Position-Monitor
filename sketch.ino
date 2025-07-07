#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <WiFi.h>
#include "ThingSpeak.h"

// --- USER CONFIGURATION ---
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
unsigned long myChannelNumber = 3004286; 
const char* myWriteAPIKey = "2ILWX7OOU0DCX2LO"; 

// --- HARDWARE INITIALIZATION (SIMULATED) ---
Adafruit_MPU6050 mpu;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for serial port to connect

  // --- Initialize Hardware ---
  setupOLED();
  setupMPU6050();

  // --- Connect to WiFi and ThingSpeak ---
  connectWiFi();
  ThingSpeak.begin(client);
}

void loop() {
  // Get sensor data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Display data on OLED
  updateOLED(a, g);

  // Send data to ThingSpeak
  updateThingSpeak(a, g);

  // Wait 20 seconds before sending the next update
  Serial.println(F("Waiting 20 seconds to send next update..."));
  delay(20000);
}

// --- HELPER FUNCTIONS ---

void setupOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("System Initializing..."));
  display.display();
}

void setupMPU6050() {
  if (!mpu.begin()) {
    Serial.println(F("Failed to find MPU6050 chip"));
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("MPU6050 Error!"));
    display.display();
    while (1) { delay(10); }
  }
  Serial.println(F("MPU6050 Found!"));
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void connectWiFi() {
  Serial.print(F("Connecting to WiFi..."));
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Connecting to WiFi..."));
  display.display();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
    delay(500);
    Serial.print(F("."));
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("\nWiFi connected!"));
    Serial.print(F("IP Address: "));
    Serial.println(WiFi.localIP());
    display.println(F("WiFi Connected!"));
    display.display();
  } else {
    Serial.println(F("\nWiFi connection failed!"));
    display.println(F("WiFi Failed!"));
    display.display();
    while (1) delay(10); // Halt if WiFi fails
  }
  delay(1000);
}

void updateOLED(sensors_event_t& a, sensors_event_t& g) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Acc")); // Label for Accelerometer

  display.setCursor(0, 16); // Values for Accelerometer
  char buffer1[30];
  snprintf(buffer1, sizeof(buffer1), "(%.2f, %.2f, %.2f)", a.acceleration.x, a.acceleration.y, a.acceleration.z);
  display.println(buffer1);

  display.setCursor(0, 32); // Label for Gyroscope
  display.println(F("Gyr"));

  display.setCursor(0, 48); // Values for Gyroscope
  char buffer2[30];
  snprintf(buffer2, sizeof(buffer2), "(%.2f, %.2f, %.2f)", g.gyro.x, g.gyro.y, g.gyro.z);
  display.println(buffer2);

  display.display();
}

void updateThingSpeak(sensors_event_t& a, sensors_event_t& g) {
  // Set the fields with the sensor values
  ThingSpeak.setField(1, a.acceleration.x);
  ThingSpeak.setField(2, a.acceleration.y);
  ThingSpeak.setField(3, a.acceleration.z);
  ThingSpeak.setField(4, g.gyro.x);
  ThingSpeak.setField(5, g.gyro.y);
  ThingSpeak.setField(6, g.gyro.z);

  // Write to the ThingSpeak channel
  int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (httpCode == 200) {
    Serial.println(F("Channel update successful."));
  } else if (httpCode == 0) {
    Serial.println(F("ThingSpeak update failed: No internet connection (simulated)."));
  } else {
    String errorMsg = F("Problem updating channel. HTTP error code ");
    errorMsg += String(httpCode);
    Serial.println(errorMsg);
  }
}