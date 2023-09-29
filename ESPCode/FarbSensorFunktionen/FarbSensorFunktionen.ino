#include <Wire.h>
#include "Adafruit_TCS34725.h"

//initialisierung beider Farbsensoren
Adafruit_TCS34725 tcsKante = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcsEcke = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

//Funktion zur Auswahl des Multiplexerkanals
void PCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // PCA9548A addresse ist 0x70
  Wire.write(1 << bus);          //Byte senden zur Auswahl des Kanals
  Wire.endTransmission();
}

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





void setup() {
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
