




#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcsKante = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

Adafruit_TCS34725 tcsEcke = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);


void PCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // PCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}






int SAMPLES[][4];




void setup() {
  Serial.begin(9600);

  Wire.begin();

  PCA9548A(0);

  if (tcsKante.begin()) {
    Serial.println("Found sensor Kante");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  PCA9548A(1);

  if (tcsEcke.begin()) {
    Serial.println("Found sensor Ecke");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }





  // Now we're ready to get readings!
}

void loop() {


  PCA9548A(0);

  uint16_t r, g, b, c, colorTemp, lux;

  tcsKante.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcsKante.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcsKante.calculateLux(r, g, b);
  Serial.print("Sensor an der Kante: ");
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  if (r >= 530 && r <= 580 && g >= 890 && g <= 940 && b >= 540 && b <= 600) {
    
    Serial.println(" ");
    Serial.println("Kante");
    Serial.print("Gelb!");
    Serial.println(" ");
    Serial.println(" ");
  }
  else if (r >= 280 && r <= 330 && g >= 690 && g <= 740 && b >= 490 && b <= 540) {
    
    Serial.println(" ");
    Serial.println("Kante");
    Serial.print("Grün!");
    Serial.println(" ");
    Serial.println(" ");      
  }
  else if (r >= 600 && r <= 650 && g >= 490 && g <= 550 && b >= 450 && b <= 500) {
    
    Serial.println(" ");
    Serial.println("Kante");
    Serial.print("Orange!");
    Serial.println(" ");
    Serial.println(" ");      
  }
  else if (r >= 285 && r <= 330 && g >= 465 && g <= 510 && b >= 420 && b <= 460) {
    
    Serial.println(" ");
    Serial.println("Kante");
    Serial.print("Rot!");
    Serial.println(" ");
    Serial.println(" ");      
  }
  else if (r >= 470 && r <= 520 && g >= 830 && g <= 900 && b >= 760 && b <= 800) {
    
    Serial.println(" ");
    Serial.println("Kante");
    Serial.print("Weiß!");
    Serial.println(" ");
    Serial.println(" ");      
  }
  else if (r >= 220 && r <= 260 && g >= 480 && g <= 530 && b >= 490 && b <= 540) {
    
    Serial.println(" ");
    Serial.println("Kante");
    Serial.print("Blau!");
    Serial.println(" ");
    Serial.println(" ");      
  }

  delay(1000);

  PCA9548A(1);

 // uint16_t r, g, b, c, colorTemp, lux;

  tcsEcke.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcsEcke.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcsEcke.calculateLux(r, g, b);
  Serial.print("Sensor an der Ecke: ");
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  if (r >= 530 && r <= 590 && g >= 820 && g <= 890 && b >= 500 && b <= 550) {
    
    Serial.println(" ");
    Serial.println("Ecke");
    Serial.print("Gelb!");
    Serial.println(" ");
    Serial.println(" ");
  }
  else if (r >= 290 && r <= 350 && g >= 655 && g <= 720 && b >= 465 && b <= 500) {
    
    Serial.println(" ");
    Serial.println("Ecke");
    Serial.print("Grün!");
    Serial.println(" ");
    Serial.println(" ");      
  }
  else if (r >= 630 && r <= 685 && g >= 480 && g <= 510 && b >= 430 && b <= 460) {

    Serial.println(" ");
    Serial.println("Ecke");
    Serial.print("Orange!");
    Serial.println(" ");
    Serial.println(" ");      
  }
  else if (r >= 300 && r <= 375 && g >= 430 && g <= 515 && b >= 390 && b <= 440) {
    
    Serial.println(" ");
    Serial.println("Ecke");
    Serial.print("Rot!");
    Serial.println(" ");
    Serial.println(" ");      
  }
  else if (r >= 470 && r <= 515 && g >= 760 && g <= 815 && b >= 680 && b <= 735) {
    
    Serial.println(" ");
    Serial.println("Ecke");
    Serial.print("Weiß!");
    Serial.println(" ");
    Serial.println(" ");      
  }
  else if (r >= 235 && r <= 300 && g >= 465 && g <= 540 && b >= 460 && b <= 500) {
    
    Serial.println(" ");
    Serial.println("Ecke");
    Serial.print("Blau!");
    Serial.println(" ");
    Serial.println(" ");      
  }
    




  delay(1000);
}


  
  




