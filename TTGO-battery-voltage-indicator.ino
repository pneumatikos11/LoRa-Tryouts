#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_SDA 21
#define OLED_SCL 22 
#define OLED_RST 16
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

const uint8_t blue = 2;
const uint8_t batteryPin = 35;
float batteryVoltage;  

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup() 
{
  Serial.begin(115200);
  pinMode(blue, OUTPUT);
  pinMode(batteryPin, INPUT);

  pinMode (16, OUTPUT);
  digitalWrite (16, LOW); // set GPIO16 low to reset OLED
  delay (50);
  digitalWrite (16, HIGH); // while OLED is running, GPIO16 must go high
  
 Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
}
char string[25];
void displayVolatge(float batteryVoltage) {
    display.setCursor(0,0);
    display.print("Battery  ");
    display.print("Monitoring");
    display.setCursor(0,10);
    itoa(batteryVoltage,string,10);
    sprintf(string,"%7.5f",batteryVoltage);
    display.print(string);
    display.setCursor(0,20);
}

void loop() 
{
  digitalWrite(blue, 1);
  delay(100);
  digitalWrite(blue, 0);
  delay(100);
  digitalWrite(blue, 1);
  delay(100);
  
  batteryVoltage = (float)(analogRead(batteryPin)) / 4095*2*3.3*1.1;
  Serial.print("Battery Voltage = "); 
  Serial.print(batteryVoltage); 
  Serial.println("V");
  display.clearDisplay();
  displayVolatge(batteryVoltage);
  display.display();
  digitalWrite(blue, 0);
  delay(500);

}
