#include <MD_DS1307.h>
#include <Wire.h>
#define A1 3
#define B1 4
#define C1 5
#define D1 6
#define A2 7
#define B2 8
#define C2 9
#define D2 10
#define A3 11
#define B3 12
#define C3 13
#define D3 14
#define A4 15
#define B4 16
#define C4 2
#define D4 1
#define pot A3
char A[4] = {A1, A2, A3, A4};
char B[4] = {B1, B2, B3, B4};
char C[4] = {C1, C2, C3, C4};
char D[4] = {D1, D2, D3, D4};
int zero;
int one;
int two;
int three;
int hour;
int minute;

String command;
//int test = 0;

// time programming using https://github.com/MajicDesigns/MD_DS1307/tree/master
// MD_DS1307 test sketch
// in serial (set baud to 57600)
// tw 20240218 084900 6

void setup() {
  pinMode(A1, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(B4, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(pot, INPUT);
  for (char i = 0; i < 4; i++) {
    digitalWrite(A[i], HIGH);
    digitalWrite(B[i], HIGH);
    digitalWrite(C[i], HIGH);
    digitalWrite(D[i], HIGH);
  }
  if (!RTC.isRunning())
    RTC.control(DS1307_CLOCK_HALT, DS1307_OFF);

  // WARNING: la porta seriale attiva non fa funzionare correttamente l'orologio
  // utilizzare SOLO per configurare l'ora e poi rimuovere!!!!
  //Serial.begin(9600);
  //showHelp();

  // welcome message
  // 18 02
  writenumber(0, 1);
  writenumber(1, 8);
  writenumber(2, 0);
  writenumber(3, 2);
  delay(2000);
  // 20 24
  writenumber(0, 2);
  writenumber(1, 0);
  writenumber(2, 2);
  writenumber(3, 4);
  delay(2000);

  // daylight saving time hack
  // ora legale:domenica 30-31 marzo: h += 1
  // if (weekday == Sunday && month == 3 && 25 <= day <= 31 && hour > 3) { hour += 1
    // ora solare:
  // domenica 27 ottobre: h -= 1
  // if (weekday == Sunday && month == 10 && 25 <= day <= 31 && hour > 3) { hour -= 1
    if ((RTC.dow == 1) && (RTC.mm == 3) && (25 <= RTC.dd <= 31) && (RTC.h > 3)) {
      RTC.h = RTC.h + 1;
        // one shifting leftwards
        writenumber(0, 0);
        writenumber(1, 0);
        writenumber(2, 0);
        writenumber(3, 1);
        delay(1000);
        writenumber(0, 0);
        writenumber(1, 0);
        writenumber(2, 1);
        writenumber(3, 0);
        delay(1000);
        writenumber(0, 0);
        writenumber(1, 1);
        writenumber(2, 0);
        writenumber(3, 0);
        delay(1000);
        writenumber(0, 1);
        writenumber(1, 0);
        writenumber(2, 0);
        writenumber(3, 0);
        delay(1000);
    } else if ((RTC.dow == 1) && (RTC.mm == 10) && (25 <= RTC.dd <= 31) && (RTC.h > 3)) {
      RTC.h = RTC.h - 1;
        // one shifting rightward
        writenumber(0, 1);
        writenumber(1, 0);
        writenumber(2, 0);
        writenumber(3, 0);
        delay(1000);
        writenumber(0, 0);
        writenumber(1, 1);
        writenumber(2, 0);
        writenumber(3, 0);
        delay(1000);
        writenumber(0, 0);
        writenumber(1, 0);
        writenumber(2, 1);
        writenumber(3, 0);
        delay(1000);
        writenumber(0, 0);
        writenumber(1, 0);
        writenumber(2, 0);
        writenumber(3, 1);
        delay(1000);
    }
}

void loop() {
  RTC.readTime();
  hour = RTC.h;
  minute = RTC.m;
  zero = (hour / 10) % 10;
  one = hour % 10;
  two =  (minute / 10) % 10;
  three = minute % 10;

  
  writenumber(0, zero);
  writenumber(1, one);
  writenumber(2, two);
  writenumber(3, three);
  
  /*
  writenumber(0, test);
  writenumber(1, test);
  writenumber(2, test);
  writenumber(3, test);
  */

  delay(1000);
  /*
  test = test +1;
  if (test > 9) {
    test = 0;
  }
  */

  /*
  if (Serial.available() > 0) {
    command = Serial.readStringUntil("\n");
    if (command.substring(0, 2)=="wt") {
      RTC.h = command.substring(2, 4).toInt();
      RTC.m = command.substring(4,6).toInt();
      RTC.s = 0;
      RTC.writeTime();
      Serial.print("[ ^.^ ] time configured to: ");
      Serial.print(RTC.h);
      Serial.print(" : ");
      Serial.print(RTC.m);
      Serial.println();
    } else if (command.substring(0, 2)=="rt") {
      Serial.print("[ ^.^ ] current time is: ");
      Serial.print(RTC.h);
      Serial.print(" : ");
      Serial.print(RTC.m);
      Serial.println();
    } else if (command.substring(0,4)=="help") {
      showHelp();
    } else {
      Serial.println("[ X.X ] Invalid data!");
    }
  }
  */
}

void writenumber(int a, int b) {
  switch (b) {
    case 0:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 9:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 8:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 7:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 6:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 5:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 4:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 3:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 2:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
    case 1:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
  }
}

void off(int a) {
  digitalWrite(A[a], HIGH);
  digitalWrite(B[a], HIGH);
  digitalWrite(C[a], HIGH);
  digitalWrite(D[a], HIGH);
}
