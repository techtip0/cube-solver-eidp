//AccelStepper Library inculdieren
#include <AccelStepper.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"


//Pins für serielle Verbindung definieren
#define RXD2 16 
#define TXD2 17

//initialisierung beider Farbsensoren
Adafruit_TCS34725 tcsKante = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcsEcke = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

//Funktion zur Auswahl des Multiplexerkanals
void PCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // PCA9548A addresse ist 0x70
  Wire.write(1 << bus);          //Byte senden zur Auswahl des Kanals
  Wire.endTransmission();
}

//Funktionen zum Scannen der Farben an den einzelnen Sensoren
char KanteScan(){
  uint16_t r, g, b, c;
  char ErgebnisKante;
  PCA9548A(0);
  tcsKante.getRawData(&r, &g, &b, &c);
  //gelb
  if (r >= 530 && r <= 580 && g >= 890 && g <= 940 && b >= 540 && b <= 600) {
    char ErgebnisKante = 'U';
  }
  //grün
  else if (r >= 280 && r <= 330 && g >= 690 && g <= 740 && b >= 490 && b <= 540) {
    char ErgebnisKante = 'L';
  }
  //orange
  else if (r >= 600 && r <= 650 && g >= 490 && g <= 550 && b >= 450 && b <= 500) {
    char ErgebnisKante = 'F';
  }
  //rot
  else if (r >= 285 && r <= 330 && g >= 465 && g <= 510 && b >= 420 && b <= 460) {
   char ErgebnisKante = 'B';
  }
  //weiß
  else if (r >= 470 && r <= 520 && g >= 830 && g <= 900 && b >= 760 && b <= 800) {
   char ErgebnisKante = 'D';
  }
  //blau
  else if (r >= 220 && r <= 260 && g >= 480 && g <= 530 && b >= 490 && b <= 540) {
    char ErgebnisKante = 'R';
  }  
  return ErgebnisKante;
}  

char EckeScan(){
  uint16_t r, g, b, c;
  char ErgebnisEcke;
  PCA9548A(1);

  tcsEcke.getRawData(&r, &g, &b, &c);
  //gelb
  if (r >= 530 && r <= 590 && g >= 820 && g <= 890 && b >= 500 && b <= 550) {
    char ErgebnisEcke = 'U';
    
  }
  //grün
  else if (r >= 290 && r <= 350 && g >= 655 && g <= 720 && b >= 465 && b <= 500) {
    char ErgebnisEcke = 'L';    
  }
  //orange
  else if (r >= 630 && r <= 685 && g >= 480 && g <= 510 && b >= 430 && b <= 460) {
    char ErgebnisEcke = 'F';  
  }
  //rot
  else if (r >= 300 && r <= 375 && g >= 430 && g <= 515 && b >= 390 && b <= 440) {
    char ErgebnisEcke = 'B';    
  }
  //weiß
  else if (r >= 470 && r <= 515 && g >= 760 && g <= 815 && b >= 680 && b <= 735) {
    char ErgebnisEcke = 'D';
  }
  //blau
  else if (r >= 235 && r <= 300 && g >= 465 && g <= 540 && b >= 460 && b <= 500) {
    char ErgebnisEcke = 'R';     
  }

  return ErgebnisEcke;

}


//Funktion zum warten via Millis(), da delay() ESP32 blockiert
void warten(long intervall){
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();
  while(currentMillis - previousMillis < intervall){
    currentMillis = millis();
  }
}


void Scan()
{

  String CubeDefinitionString = "XXXXUXXXXXXXXRXXXXXXXXFXXXXXXXXDXXXXXXXXLXXXXXXXXBXXXX";   //Erstellen eines Cube Strings im Richtigen Format; dieser wird als Input für den Lösealgorythmus genutzt
                                                                                            //X als Platzhalter für eingelsenen Werte

  CubeDefinitionString.setCharAt(5, KanteScan());        //Austauschen der Platzhalter an den richtigen Stellen im String gegen die eingescannten Werte
  warten(1000);                                           //Kurzer Delay, um Multiplexer und Farbsensor Zeit zu geben
  CubeDefinitionString.setCharAt(0, EckeScan());         //Das Austauschen und das Drehen erfolgt nach einer vorher festgelegten Sequenz und Prositionen

  U1();                                                 //Drehen des Würfels damit alle Sticker eingescannt werden
  warten(1000);

  CubeDefinitionString.setCharAt(1, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(6, EckeScan());

  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(3, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(8, EckeScan());

  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(7, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(2, EckeScan());

  U1();
  R1();
  L3();
  warten(1000);

  CubeDefinitionString.setCharAt(23, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(18, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(21, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(26, EckeScan());

  U2();
  R3();
  L1();
  F1();
  R1();
  L3();
  warten(1000);

  CubeDefinitionString.setCharAt(19, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(24, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(25, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(20, EckeScan());

  U2();
  R3();
  L1();
  F3();
  R2();
  L2();
  warten(1000);

  CubeDefinitionString.setCharAt(32, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(27, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(30, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(35, EckeScan());

  U2();
  R1();
  L2();
  D1();
  R2();
  L2();
  warten(1000);

  CubeDefinitionString.setCharAt(28, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(33, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(34, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(29, EckeScan());

  U2();
  R2();
  L2();
  D3();
  R3();
  L1();
  warten(1000);

  CubeDefinitionString.setCharAt(48, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(53, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(50, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(45, EckeScan());

  U2();
  R1();
  L3();
  Bone();
  R3();
  L1();
  warten(1000);

  CubeDefinitionString.setCharAt(52, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(47, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(46, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(51, EckeScan());

  U2();
  R1();
  L3();
  B3();
  B3();
  F1();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(39, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(44, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(41, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(36, EckeScan());

  U1();
  F3();
  Bone();
  L1();
  F1();
  B3();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(43, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(38, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(37, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(42, EckeScan());

  U1();
  F3();
  Bone();
  L3();
  F3();
  Bone();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(14, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(9, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(12, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(17, EckeScan());

  U1();
  F1();
  B3();
  R1();
  F3();
  Bone();
  U1();
  warten(1000);

  CubeDefinitionString.setCharAt(10, KanteScan());
  warten(1000);
  CubeDefinitionString.setCharAt(15, EckeScan());

  U2();
  warten(1000);

  CubeDefinitionString.setCharAt(16, KanteScan());
  CubeDefinitionString.setCharAt(11, EckeScan());

  U1();
  F1();
  B3();
  R3();

  Serial2.print(CubeDefinitionString + "\n");


}

// Defnieren der Motoren-Pinne

const int gruendirPin = 14;
const int gruenstepPin = 27;

const int weissdirPin = 18;
const int weissstepPin = 5;

const int rotdirPin = 13;
const int rotstepPin = 12;

const int orangedirPin = 2;
const int orangestepPin = 15;

const int blaudirPin = 33;
const int blaustepPin = 32;

const int gelbdirPin = 26;
const int gelbstepPin = 25;




// Motor interface typ definieren
#define motorInterfaceType 1

// Motoren als Instancen erstellen
AccelStepper gruen(motorInterfaceType, gruenstepPin, gruendirPin);
AccelStepper weiss(motorInterfaceType, weissstepPin, weissdirPin);
AccelStepper rot(motorInterfaceType, rotstepPin, rotdirPin);
AccelStepper orange(motorInterfaceType, orangestepPin, orangedirPin);
AccelStepper blau(motorInterfaceType, blaustepPin, blaudirPin);
AccelStepper gelb(motorInterfaceType, gelbstepPin, gelbdirPin);


// 90-Grad drehungen aller Seiten in beide Richungen als Funktionen definieren
//D1 bedeutet einmal im Uhrzeigersinn, D2 zweimal
//D3 einmal rückwärts
void D3() {
  weiss.move(800);
  weiss.runToPosition();
}
void D2() {
  weiss.move(1600);
  weiss.runToPosition();
}
void D1() {
  weiss.move(-800);
  weiss.runToPosition();
}

void U1() {
  gelb.move(800);
  gelb.runToPosition();
}
void U2() {
  gelb.move(1600);
  gelb.runToPosition();
}
void U3() {
  gelb.move(-800);
  gelb.runToPosition();
}

void L3() {
  gruen.move(800);
  gruen.runToPosition();
}
void L2() {
  gruen.move(1600);
  gruen.runToPosition();
}
void L1() {
  gruen.move(-800);
  gruen.runToPosition();
}

void B3() {
  rot.move(800);
  rot.runToPosition();
}
void B2() {
  rot.move(1600);
  rot.runToPosition();
}
void Bone() {
  rot.move(-800);
  rot.runToPosition();
}

void F3() {
  orange.move(800);
  orange.runToPosition();
}
void F2() {
  orange.move(1600);
  orange.runToPosition();
}
void F1() {
  orange.move(-800);
  orange.runToPosition();
}

void R3() {
  blau.move(800);
  blau.runToPosition();
}
void R2() {
  blau.move(1600);
  blau.runToPosition();
}
void R1() {
  blau.move(-800);
  blau.runToPosition();
}


String RPiEmpfangen(){
  while (Serial2.available() == 0){}
  String received = Serial2.readString();
  received.trim();
  return received;
}




void Verdrehen()
{
  //string wird von Rasberry Pi empfangen


  // Definiere String
  String strVerdreh = RPiEmpfangen();

  //String durchgehen und drehen
  for(int i = 0; i <= strVerdreh.length(); i++){
    if (strVerdreh[i] == 'D')
    {
      D1();
    }

    else if (strVerdreh[i] == 'U')
    {
      U1();
    }

    else if (strVerdreh[i] == 'L')
    {
      L1();
    }

    else if (strVerdreh[i] == 'B')
    {
      Bone();
    }

    else if (strVerdreh[i] == 'F')
    {
      F1();
    }

    else if (strVerdreh[i] == 'R')
    {
      R1();
    }  
  }
  strVerdreh = "";

  Serial2.print('Fertig');
}



void setup() {

  //Serielle und I2C Verbindung öffnen
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Wire.begin();

	// Festsetzen der Maximalgeschwinigkeit und Beschleunigungsfaktoren der Motoren
	// initial speed and the target position
	gruen.setMaxSpeed(20000);
	gruen.setAcceleration(10000);
	gruen.setSpeed(20000);
	

  weiss.setMaxSpeed(20000);
	weiss.setAcceleration(10000);
	weiss.setSpeed(20000);

  rot.setMaxSpeed(20000);
	rot.setAcceleration(10000);
	rot.setSpeed(20000);


  orange.setMaxSpeed(20000);
	orange.setAcceleration(10000);
	orange.setSpeed(20000);


  blau.setMaxSpeed(20000);
	blau.setAcceleration(10000);
	blau.setSpeed(20000);


  gelb.setMaxSpeed(20000);
	gelb.setAcceleration(10000);
	gelb.setSpeed(20000);

}



void loop ()
{
  Verdrehen();
  String weiter = RPiEmpfangen();
  while (weiter != "GO"){}
  weiter = "";
  Scan();
};