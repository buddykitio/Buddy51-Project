#ifndef _HC_SR04_H_
#define _HC_SR04_H_

#include "../system.h"
#include <8052.h>
#include "../type.h"

int getDistance();

/* Pin Definitions - Modify these based on your hardware connections */
#define ECHO P1_0
#define TRIG P1_1

#endif