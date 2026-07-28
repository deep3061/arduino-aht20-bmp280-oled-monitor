#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

bool oledReady = false;
bool ahtReady = false;
bool bmpReady = false;

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 2000;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println(F("Starting environmental monitor..."));

  oledReady = display.begin(
    SSD1306_SWITCHCAPVCC,
    OLED_ADDRESS
  );

  if (oledReady) {
    Serial.println(F("OLED ready"));

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("Starting system..."));
    display.display();
  } else {
    Serial.println(F("OLED failed"));
  }

  ahtReady = aht.begin();

  if (ahtReady) {
    Serial.println(F("AHT20 ready"));
  } else {
    Serial.println(F("AHT20 failed"));
  }

  if (bmp.begin(0x76)) {
    bmpReady = true;
    Serial.println(F("BMP280 ready at 0x76"));
  } else if (bmp.begin(0x77)) {
    bmpReady = true;
    Serial.println(F("BMP280 ready at 0x77"));
  } else {
    bmpReady = false;
    Serial.println(F("BMP280 failed"));
  }

  if (oledReady) {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);

    display.println(F("SYSTEM STATUS"));
    display.println(F("----------------"));

    display.print(F("OLED:   "));
    display.println(oledReady ? F("OK") : F("FAIL"));

    display.print(F("AHT20:  "));
    display.println(ahtReady ? F("OK") : F("FAIL"));

    display.print(F("BMP280: "));
    display.println(bmpReady ? F("OK") : F("FAIL"));

    display.display();
  }

  delay(2000);
}

void loop() {
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();

    float ahtTemperature = NAN;
    float humidity = NAN;
    float bmpTemperature = NAN;
    float pressure = NAN;

    if (ahtReady) {
      sensors_event_t humidityEvent;
      sensors_event_t temperatureEvent;

      aht.getEvent(
        &humidityEvent,
        &temperatureEvent
      );

      ahtTemperature = temperatureEvent.temperature;
      humidity = humidityEvent.relative_humidity;
    }

    if (bmpReady) {
      bmpTemperature = bmp.readTemperature();
      pressure = bmp.readPressure() / 100.0F;
    }

    printSerial(
      ahtTemperature,
      humidity,
      bmpTemperature,
      pressure
    );

    updateOLED(
      ahtTemperature,
      humidity,
      bmpTemperature,
      pressure
    );
  }
}

void printSerial(
  float ahtTemperature,
  float humidity,
  float bmpTemperature,
  float pressure
) {
  Serial.println(F("--------------------------"));

  if (ahtReady) {
    Serial.print(F("AHT20 Temp: "));
    Serial.print(ahtTemperature, 1);
    Serial.println(F(" C"));

    Serial.print(F("Humidity: "));
    Serial.print(humidity, 1);
    Serial.println(F(" %"));
  } else {
    Serial.println(F("AHT20 unavailable"));
  }

  if (bmpReady) {
    Serial.print(F("BMP280 Temp: "));
    Serial.print(bmpTemperature, 1);
    Serial.println(F(" C"));

    Serial.print(F("Pressure: "));
    Serial.print(pressure, 1);
    Serial.println(F(" hPa"));
  } else {
    Serial.println(F("BMP280 unavailable"));
  }
}

void updateOLED(
  float ahtTemperature,
  float humidity,
  float bmpTemperature,
  float pressure
) {
  if (!oledReady) {
    return;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println(F("ENVIRONMENT MONITOR"));

  display.drawLine(
    0,
    10,
    SCREEN_WIDTH - 1,
    10,
    SSD1306_WHITE
  );

  display.setCursor(0, 15);

  if (ahtReady) {
    display.print(F("Temp: "));
    display.print(ahtTemperature, 1);
    display.println(F(" C"));

    display.print(F("Humidity: "));
    display.print(humidity, 1);
    display.println(F(" %"));
  } else {
    display.println(F("AHT20 ERROR"));
  }

  if (bmpReady) {
    display.print(F("BMP Temp: "));
    display.print(bmpTemperature, 1);
    display.println(F(" C"));

    display.print(F("Pressure: "));
    display.print(pressure, 0);
    display.println(F(" hPa"));
  } else {
    display.println(F("BMP280 ERROR"));
  }

  display.display();
}