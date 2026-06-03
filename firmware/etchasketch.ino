#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define HCLK 2//change to digital pins used for right handle
#define HDT 3
#define HSW 4
#define VCLK 6//change to digital pins used for left handle
#define VDT 7
#define VSW 8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int currentStateHCLK;
int lastStateHCLK;
int currentStateVCLK;
int lastStateVCLK;
int x = 0;
int y = 0;

void setup() {
  pinMode(HCLK, INPUT);
  pinMode(HDT, INPUT);
  pinMode(HSW, INPUT_PULLUP);
  pinMode(VCLK, INPUT);
  pinMode(VDT, INPUT);
  pinMode(VSW, INPUT_PULLUP);
  Serial.begin(9600);
  
  // Read the initial state of CLK
  lastStateHCLK = digitalRead(HCLK);
  lastStateVCLK = digitalRead(VCLK);
}

void loop() {
  // 1. Read the current state of CLK
  currentStateHCLK = digitalRead(HCLK);

  // If last and current state of CLK are different, then pulse occurred
  if (currentStateHCLK != lastStateHCLK) {
    if (digitalRead(HDT) != currentStateHCLK) {
      // left
        display.drawPixel(x-1, y, WHITE); 
    } else {
      // right
        display.drawPixel(x+1, y, WHITE); 
    }
  }  
  currentStateVCLK = digitalRead(VCLK);
  if (currentStateVCLK != lastStateVCLK) {
    if (digitalRead(VDT) != currentStateVCLK) {
      //up
        display.drawPixel(x, y+1 , WHITE); 
    } else {
      // down
        display.drawPixel(x , y-1 , WHITE); 
    }
  }
  display.display();

  // Remember last CLK state
  lastStateHCLK = currentStateHCLK;
  lastStateVCLK = currentStateVCLK;

  // if two buttons are pressed simultaneiously the screen resets
  if (digitalRead(VSW) == LOW and digitalRead(HSW) == LOW) {
    Serial.println("Clear");
    display.clearDisplay();
    delay(200); // Simple debounce for the button
  }
}