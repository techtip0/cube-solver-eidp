#include <AccelStepper.h>

//Funktion zum warten via Millis(), da delay() ESP32 blockiert
void warten(long intervall){
  unsigned long currentMillis = millis();
  unsigned long previousMillis = millis();
  while(currentMillis - previousMillis < intervall){
    currentMillis = millis();
  }
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


void setup() {
  // put your setup code here, to run once:
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

  Serial.begin(9600);
}

String CubeSolveString = "L2 L2 R2 R2 L2 L2 (19f)";

String Loesen(String CubeSolveString) 
{


  String Speicherstrg[60];

  int StringCount = 0;

  //Aufteilen den CubeSolveStrings in substrings
  while (CubeSolveString.length() > 0)
    {
      int index = CubeSolveString.indexOf(' ');
      if (index == -1)  // Keine Leertaste gefunden
      {
        Speicherstrg[StringCount++] = CubeSolveString;
        break;
      }
      else
      {
        Speicherstrg[StringCount++] = CubeSolveString.substring(0, index);
        CubeSolveString = CubeSolveString.substring(index+1);
      }
    }
    for (int i = 0; i <= StringCount; i++)
  {

    if (Speicherstrg[i] == "D1")
    {
      D1();
    }

    else if (Speicherstrg[i] == "D2")
    {
      D2();
    }

    else if (Speicherstrg[i] == "D3")
    {
      D3();
    }

    else if (Speicherstrg[i] == "U1")
    {
      U1();
    }

    else if (Speicherstrg[i] == "U2")
    {
      U2();
    }

    else if (Speicherstrg[i] == "U3")
    {
      U3();
    }

    else if (Speicherstrg[i] == "L1")
    {
      L1();
    }

    else if (Speicherstrg[i] == "L2")
    {
      L2();
    }

    else if (Speicherstrg[i] == "L3")
    {
      L3();
    }

    else if (Speicherstrg[i] == "B1")
    {
      Bone();
    }

    else if (Speicherstrg[i] == "B2")
    {
      B2();
    }

    else if (Speicherstrg[i] == "B3")
    {
      B3();
    }

    else if (Speicherstrg[i] == "F1")
    {
      F1();
    }

    else if (Speicherstrg[i] == "F2")
    {
      F2();
    }

    else if (Speicherstrg[i] == "F3")
    {
      F3();
    }

    else if (Speicherstrg[i] == "R1")
    {
      R1();
    }

    else if (Speicherstrg[i] == "R2")
    {
      R2();
    }

    else if (Speicherstrg[i] == "R3")
    {
      R3();
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Loesen(CubeSolveString);
  //Serial.println(test1[0]);
  //Serial.println(test1[5]);
  warten(1000);
  //Serial.println(CubeSolveString.length());
}
