// LCD
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x3f, 16,2); 

// sensors, leds
#define flame_sensor 7
#define buzzer A3
#define pirPin 6
#define kids_room_led 8
#define temp_sensor A0 
#define ldr A1

int flame;
int motion;
int calibrationTime;
int temp;
int light;

void setup()
{
  lcd.init();
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0,0);
  
  pinMode (flame_sensor,INPUT);
  pinMode (buzzer,OUTPUT);
  pinMode (pirPin,INPUT);
  pinMode (kids_room_led,OUTPUT);
  pinMode (A0,INPUT);  
  
  Serial.begin(9600);
  //give the sensor some time to calibrate
  for(int i = 0; i < calibrationTime; i++)
  {
    delay(1000);
  }
}

void loop() 
{
  //flame sensor
  flame = digitalRead(flame_sensor);
  
  if (flame == 1)
  {
  digitalWrite(buzzer , HIGH);
  delay (250);
  digitalWrite( buzzer , LOW);
  delay (250);
  }

  
  // motion sensor
  motion = digitalRead(pirPin);
  if (motion == 1)
  {
    delay(1000);
    digitalWrite(kids_room_led,HIGH);
  }
  if (motion == 0)
  { 
    delay(1000);
    digitalWrite(kids_room_led,LOW);
  }
  // Temperature sensor
  temp = analogRead(temp_sensor);
  temp = temp * .48828125;
  lcd.setCursor(0,0);
  lcd.print ("Tempreture:");
  lcd.setCursor(12,0); 
  lcd.print(temp);
  lcd.setCursor(15,0); 
  lcd.print("C");
  //Serial.print("temperature = " );
  //Serial.println (temp);
  //Serial.print ("°C");
  //Serial.print ("\n");
  
  //light sensor
  light = analogRead(ldr);
  if(light > 250)
  {
    lcd.setCursor(0,1);
    lcd.print("It's morning now");
  }
  if(light < 250)
  {
    lcd.setCursor(0,1);
    lcd.print("it's night now");
  }
  //Serial.print("light =   ");
  //Serial.print(light);
  //Serial.print("\n");
  
  

}
