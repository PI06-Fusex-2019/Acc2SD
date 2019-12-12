#ifndef WRITESD_H
#define WRITESD_H

#include "Arduino.h"
#include "SD.h"

template <class D> void writeOnSD(File cartesd, const char* monfichier, D data) 
{
  cartesd=SD.open(monfichier, FILE_WRITE);
  if (cartesd)
  {
    cartesd.println(data);
    cartesd.close();
  }
}


#endif