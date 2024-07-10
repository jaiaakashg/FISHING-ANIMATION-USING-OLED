#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

int fishX = 110;
int fishY = 60;
bool fishDirection = false;
bool caughtFish = false;
int manArmY = 35;
int fishCaughtY = 40;

void drawPond() {
  display.drawRect(0, 48, 128, 16, SSD1306_WHITE);
  for (int i = 0; i < 128; i += 8) {
    display.drawLine(i, 56, i + 4, 52, SSD1306_WHITE); 
    display.drawLine(i + 4, 52, i + 8, 56, SSD1306_WHITE);
  }
}

void drawBoat() {
  display.drawLine(45, 40, 83, 40, SSD1306_WHITE);
  display.drawLine(45, 40, 38, 48, SSD1306_WHITE);
  display.drawLine(83, 40, 90, 48, SSD1306_WHITE);
  display.drawLine(38, 48, 90, 48, SSD1306_WHITE);
}

void drawMan() {
  display.drawLine(64, 30, 64, 40, SSD1306_WHITE);
  display.drawCircle(64, 25, 5, SSD1306_WHITE);
  display.drawLine(64, 35, 58, 40, SSD1306_WHITE);
  display.drawLine(64, 35, 70, manArmY, SSD1306_WHITE);
  display.drawLine(64, 40, 60, 48, SSD1306_WHITE);
  display.drawLine(64, 40, 68, 48, SSD1306_WHITE);
}

void drawFishingRod() {
  display.drawLine(64, 35, 110, 48, SSD1306_WHITE);
  if (caughtFish) {
    display.drawLine(110, fishCaughtY, 110, fishCaughtY + 6, SSD1306_WHITE); 
  } else {
    display.drawLine(110, 48, 110, 54, SSD1306_WHITE); 
  }
}

void drawFish() {
  display.fillCircle(fishX, fishY, 3, SSD1306_WHITE);
  display.drawLine(fishX - 2, fishY, fishX + 2, fishY, SSD1306_BLACK); 
  display.drawLine(fishX, fishY - 2, fishX, fishY + 2, SSD1306_BLACK);
}

void updateFishPosition() {
  if (caughtFish) {
    fishX = 110; 
    fishY = fishCaughtY + 3;
    if (fishCaughtY > 35) {
      fishCaughtY--;
      manArmY--;
    }
  } else {
    if (fishDirection) {
      fishX -= 1;
      if (fishX < 10) fishDirection = false;
    } else {
      fishX += 1;
      if (fishX > 110) fishDirection = true;
    }
  }
}

void loop() {
  display.clearDisplay();
  
  drawPond();
  drawBoat();
  drawMan();
  drawFishingRod();
  drawFish();
  updateFishPosition();
  static int loopCounter = 0;
  loopCounter++;
  if (loopCounter > 200 && fishX == 110 && !caughtFish) {
    caughtFish = true;
  }

  display.display();
  delay(50);
}

