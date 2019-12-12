// Ecriture de la carte SD à partir des données de l'accelerometre
///////// Boulay Alexis /////////
////// Last révision 11/12/2019
#include <Arduino.h>
#include "Accelero.h"
#include "WriteSD.h"
#include <SD.h>

#define LED 7
File cartesd;

double aX, aY, aZ;
double gX, gY, gZ;

// Initialisation de l'accélérométre
double dt = 1e-2;
double incli = 0;
///Arduino Nano:
//SDA = A4;
//SCL = A5;
////(Same on most Arduinos)
///MPU-6050
//I2C Address: 1101000 (binary), 0x68 (hexa) when AD0 = 0 logic, 
//I2C Address: 1101001 when AD0 = 1 logic
//////IMPORTANT: When modifying Full Scale Range, be sure to change the corresponding sensor sensitivity



// Initialise la communication avec l'accélerometre
void MPU_setup();

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);

  //Initialisation de la carte SD
  if (!SD.begin(10)){
    // Indiquer que la carte est mal configurée (LED/signal)
    while (1);
  }

  //Initialisation de l'accélerometre
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(57600);
  MPU_setup();
  digitalWrite(LED,LOW);
}

void loop() {
  // Accelerometre
  AccelerationReading(aX, aY, aZ);
  AngularAccelerationReading(gX, gY, gZ);
  writeOnSD(cartesd,"test.txt",aZ/16384);

}