#ifndef _SUMO_H
#define _SUMO_H

#include <arduino.h>
#include "sharp.h"
#include "motor.h"


#define DISTANCE 22
#define COLORFLOOR 60
#define CURRECT_TIME 500
#define CURRECT_TIME2 400
#define MAXIMUM_SPEED 200
#define SEARCH_SPEED 255
#define OPTION_TIME 50
#define TIME_ATTACK 500

void sumo(void);
boolean testDistance(void);
boolean testColorFloor(void);

boolean flag = true;
int option = 0;

long timeAttackStart, timeAttackNow;

void sumo(void) {
  motorOption('0', 0, 0);
  
  long timeStart = millis();
  //timeAttackStart = millis();
  while (true) {
    long timeNow = millis();
    
    if ((timeNow - timeStart) > OPTION_TIME) {
      option++;
      timeStart = 1000;
    }

    if (testColorFloor()) {
      if (testDistance()) {
            motorOption('8', SEARCH_SPEED, SEARCH_SPEED);
        switch (option) {
          case 1:
            motorOption('8', MAXIMUM_SPEED , MAXIMUM_SPEED );
            break;
           case 2:
            motorOption('8', MAXIMUM_SPEED / 2, MAXIMUM_SPEED);
            break;
          case 3:
            motorOption('8', MAXIMUM_SPEED, MAXIMUM_SPEED / 2);
            break;
          case 4:
            motorOption('4', MAXIMUM_SPEED , MAXIMUM_SPEED );
            break;
          case 5:
            motorOption('6', MAXIMUM_SPEED , MAXIMUM_SPEED );
            break;
          default:
            motorOption('8', MAXIMUM_SPEED , MAXIMUM_SPEED );
            option = 0;
            break;
        }
      }
    }
  }
}
boolean testDistance(void) {
  int sharp_front = sharpFront.distance();
 

  if (sharp_front < DISTANCE || sharp_front < DISTANCE) {
    // frente 100%
    if (sharp_front < DISTANCE && sharp_front < DISTANCE) {
      motorOption('8', MAXIMUM_SPEED, MAXIMUM_SPEED);
    } else if (sharp_front < DISTANCE) {
      motorOption('8', MAXIMUM_SPEED, MAXIMUM_SPEED/2);
    } else {
      motorOption('8', MAXIMUM_SPEED/2, MAXIMUM_SPEED);
    }
    return false;
  }
  timeAttackStart = 500;
  return true;
}

boolean testColorFloor(void) {
  int qtr_left = analogRead(QTR_LEFT);
  int qtr_right = analogRead(QTR_RIGHT);

  if (qtr_left < COLORFLOOR || qtr_right < COLORFLOOR ) {
    if (qtr_left < COLORFLOOR && qtr_right < COLORFLOOR) {
      motorOption('2', MAXIMUM_SPEED, MAXIMUM_SPEED);
      delay(CURRECT_TIME);
     if (flag) {
        flag = false;
        motorOption('4', MAXIMUM_SPEED, MAXIMUM_SPEED);
        delay(CURRECT_TIME2);
      } else {
        flag = true;
        motorOption('6', MAXIMUM_SPEED, MAXIMUM_SPEED);
        delay(CURRECT_TIME2);
      } 
    } else if (qtr_left < COLORFLOOR) {
      motorOption('2', MAXIMUM_SPEED, MAXIMUM_SPEED);
      delay(CURRECT_TIME);
      motorOption('4', MAXIMUM_SPEED, MAXIMUM_SPEED);
      delay(CURRECT_TIME2);
      flag = true;
    } else if (qtr_right < COLORFLOOR) {
      motorOption('2', MAXIMUM_SPEED, MAXIMUM_SPEED);
      delay(CURRECT_TIME);
      motorOption('6', MAXIMUM_SPEED, MAXIMUM_SPEED);
      delay(CURRECT_TIME2);
      flag = false;
    } else {
      motorOption('8', MAXIMUM_SPEED, MAXIMUM_SPEED);
      delay(CURRECT_TIME2);
    }
    return false;
  }
  return true;
}
#endif
