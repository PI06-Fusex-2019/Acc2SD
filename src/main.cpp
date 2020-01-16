// Ecriture de la carte SD à partir des données de l'accelerometre
///////// Boulay Alexis /////////
////// Last révision 11/12/2019

#include <Arduino.h>
#include "Accelero.h"
#include "WriteSD.h"
#include <SD.h>
#include "Integrator.h"

#define LED 7
File cartesd;

double aX, aY, aZ;
double gX, gY, gZ;
double vX(0), vY(0), vZ(0);

unsigned long time, clign;
bool etatled;

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

  time = millis();
  clign = millis();
  writeOnSD(cartesd,"test.txt","Nouvelles acquisitions \n");
}

void loop() {
  // Accelerometre
  while(millis()-time < 6000) //NE PAS OUBLIER DE REMETTRE 1 MINUTE 
  { 
    AccelerationReading(aX, aY, aZ);
    AngularAccelerationReading(gX, gY, gZ);

    writeOnSD(cartesd,"test.txt","aX=");
    writeOnSD(cartesd,"test.txt",aX/16384);

    writeOnSD(cartesd,"test.txt"," | ay=");
    writeOnSD(cartesd,"test.txt",aY/16384);

    writeOnSD(cartesd,"test.txt"," | aZ=");
    writeOnSD(cartesd,"test.txt",aZ/16384);

    writeOnSD(cartesd,"test.txt","\n");
  }
  if (millis()-clign > 500)
  {
    clign = millis();
    etatled = !etatled;
  }
  digitalWrite(LED,etatled);
}