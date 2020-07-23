#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

double sensorValue=0;
double sensorValue1=0;
int crosscount=0;
int climbhill=0;
double VmaxD=0;
double VeffD;
double Veff;
#define Relay 9
void setup()
{
  lcd.begin();
Serial.begin(9600);
lcd.backlight();

pinMode(Relay, OUTPUT);
}
void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("VOLTAGE:");

  lcd.setCursor(9,0);
  lcd.print(Veff);

digitalWrite(Relay,HIGH);
  
  if(0 > Veff < 130)
   {
    lcd.setCursor(0,1);
    lcd.print("Under Voltage");
    digitalWrite(Relay,LOW);
   }

   
   
   if(Veff > 200)
    {
      lcd.setCursor(0,1);
      lcd.print("Over Voltage");
      digitalWrite(Relay,LOW);
    }
sensorValue1=sensorValue;
delay(100);
sensorValue = analogRead(A0);
if (sensorValue>sensorValue1 && sensorValue>511){
  climbhill=1;
  VmaxD=sensorValue;
  }
if (sensorValue<sensorValue1 && climbhill==1){
  climbhill=0;
  VmaxD=sensorValue1;
  VeffD=VmaxD/sqrt(2);
  Veff=(((VeffD-420.76)/-90.24)*-210.2)+210.2;
  Serial.println(Veff);
  VmaxD=0;
}
}
