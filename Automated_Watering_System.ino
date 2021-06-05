#include <LiquidCrystal_I2C.h>

#include <DS3231.h>
#include <Wire.h>


DS3231 Clock;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int Channel = 7;
bool h12Flag;
bool pmFlag;
byte hrs;
byte mins;
byte sec;
bool Century=false;
String ssec;
String lcdsec;
String smins;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  lcd.begin();

  pinMode(Channel, OUTPUT);
  /*
    Clock.setClockMode(false);
  Clock.setYear(21);
    Clock.setMonth(5);
    Clock.setDate(28);
    Clock.setDoW(5);
    Clock.setHour(22);
    Clock.setMinute(27);
    Clock.setSecond(0);
*/
    
}


void loop() {
  // put your main code here, to run repeatedly:
hrs = (Clock.getHour(h12Flag, pmFlag));
mins = (Clock.getMinute());
sec = (Clock.getSecond());

ssec = String(sec)+ " ";
ssec.remove(2, 1);

smins = String(mins);
if (smins.length()< 2) {
  smins = "0" + smins;
}
else{
  smins = smins;
}

if (mins >= 40 && mins < 41) {
  digitalWrite(Channel, LOW);

}else {
  digitalWrite(Channel, HIGH);
}
 if (sec < 10) {
    lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(hrs);
  lcd.print(":");
  lcd.print(smins);
  lcd.print(":");
  lcd.print('0');
  lcd.print(ssec);
}



else {
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(hrs);
  lcd.print(":");
  lcd.print(smins);
  lcd.print(":"); 
  lcd.print(ssec);
}

if (mins >= 40 && mins < 41) {
  lcd.setCursor(0, 1);
  lcd.print("Water Flow: ON ");

}else {
    lcd.setCursor(0, 1);
    lcd.print("Water Flow: OFF ");
}

}
