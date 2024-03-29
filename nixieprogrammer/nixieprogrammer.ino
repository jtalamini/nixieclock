#include <MD_DS1307.h>
#include <Wire.h>

int zero;
int one;
int two;
int three;
int hour;
int minute;
String command;

void setup() {
  if (!RTC.isRunning())
    RTC.control(DS1307_CLOCK_HALT, DS1307_OFF);

  // WARNING
  Serial.begin(9600);
  showHelp();
}

void loop() {
  RTC.readTime();
  hour = RTC.h;
  minute = RTC.m;
  zero = (hour / 10) % 10;
  one = hour % 10;
  two =  (minute / 10) % 10;
  three = minute % 10;
  
  if (Serial.available() > 0) {
    command = Serial.readStringUntil("\n");
    if (command.substring(0, 2)=="wt") {
      RTC.h = command.substring(2, 4).toInt();
      RTC.m = command.substring(4,6).toInt();
      RTC.s = 0;
      RTC.writeTime();
      Serial.print("[ + ] time configured to: ");
      showTime();
    } else if (command.substring(0, 2)=="wd") {
      RTC.yyyy = command.substring(2, 6).toInt();
      RTC.mm = command.substring(6,8).toInt();
      RTC.dd = command.substring(8,10).toInt();
      RTC.writeTime();
      Serial.print("[ + ] date configured to: ");
      showDate();
    } else if (command.substring(0, 3)=="wwd") {
      RTC.dow = command.substring(3, 4).toInt();
      RTC.writeTime();
      Serial.print("[ + ] WeekDay configured to: ");
      showWeekDay();
    }else if (command.substring(0, 2)=="rt") {
      Serial.print("[ + ] Reading configuration");
      Serial.println();
      Serial.print("[ + ] date: ");
      showDate();
      Serial.println();
      Serial.print("[ + ] time: ");
      showTime();
      Serial.println();
      Serial.print("[ + ] Week Day: ");
      showWeekDay();
      Serial.println();
    } else if (command.substring(0,4)=="help") {
      showHelp();
    } else {
      Serial.println("[ - ] Invalid command");
    }
  }
}

void showHelp() {
  Serial.println("[ ! ] serial communication enabled. Usage:");
  Serial.println("    'rt' to get the RTC current time");
  Serial.println("    'wthhmm' to set the RTC time to hh:mm");
  Serial.println("    'wdYYYYMMDD' to set the RTC date to YYYY/MM/DD");
  Serial.println("    'wwd[1-7]' to set the RTC Week Day");
  Serial.println("        1 = Sunday");
  Serial.println("        2 = Monday");
  Serial.println("        3 = Tuesday");
  Serial.println("        4 = Wednesday");
  Serial.println("        5 = Thursday");
  Serial.println("        6 = Friday");
  Serial.println("        7 = Saturday");
  Serial.println("    'help' to show this message again");
  Serial.println();
}

void showTime() {
    Serial.print(RTC.h);
    Serial.print(" : ");
    Serial.print(RTC.m);
    Serial.print(" : ");
    Serial.print(RTC.s);
}

void showDate() {
      Serial.print(RTC.yyyy);
      Serial.print("/");
      Serial.print(RTC.mm);
      Serial.print("/");
      Serial.print(RTC.dd);
}

void showWeekDay() {
  switch (RTC.dow) {
    case 1: Serial.println("Sunday"); break;
    case 2: Serial.println("Monday"); break;
    case 3: Serial.println("Tuesday"); break;
    case 4: Serial.println("Wednesday"); break;
    case 5: Serial.println("Thursday"); break;
    case 6: Serial.println("Friday"); break;
    case 7: Serial.println("Saturday"); break;
    default:
      Serial.println("Invalid WeekDay");
  }

}
