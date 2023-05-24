#ifndef _CONTROL_H
#define _CONTROL_H

#include <arduino.h>
#include "qtr.h"
#include "motor.h"
#include "sharp.h"
#include "sumo.h"

void advancedOption(char option) {
  // Função para controlar as opções avançadas
  switch (option) {
    case '0':
    case '2':
    case '4':
    case '6':
    case '8':
      motorOption(option, 255, 255);
      break;
   
    case 'b':
      readFloor();
      break;
    case 'c':
      readDistance();
      break;
    case 'x':
      sumo();
      break;
  }
}

#endif
