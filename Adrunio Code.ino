#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
SoftwareSerial mySerial(11, 13);

int moist = 2;
int pump = 3;
int mois, mois1, rain;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(moist, INPUT);


  lcd.setCursor(0, 0);
  lcd.print("    MOISTURE    ");
  lcd.setCursor(0, 1);
  lcd.print("   MONITORING   ");

}

void loop() {
  digitalWrite(pump , LOW);

  mois = digitalRead(moist);

  Serial.print(mois);
  Serial.println();
  if (mois == HIGH)
  {
    digitalWrite(pump , HIGH); SendMessage();
    Serial.print("!!!LEVEL:LOW !!!");
    Serial.println();
    lcd.setCursor(0, 0);
    lcd.print("    MOISTURE    ");
    lcd.setCursor(0, 1);
    lcd.print("!!!LEVEL:LOW !!!");
    delay(500);  digitalWrite(pump , LOW);
  }
  else
  {
    digitalWrite(pump , LOW);
    lcd.setCursor(0, 0);
    lcd.print("    MOISTURE    ");
    lcd.setCursor(0, 1);
    lcd.print("!!LEVEL:NORMAL!!");
    Serial.print("!!!LEVEL:NORMAL!!!");
    Serial.println();

    delay(500);
  }
  if (Serial.available() > 0)
  {
    if (mySerial.available() > 0)
      Serial.write(mySerial.read());
  }

}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+91xxxxx\"\r");
  delay(1000);
  mySerial.println("!!!STARTING>>>>>>!!!");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}
