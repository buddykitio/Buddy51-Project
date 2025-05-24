#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <8052.h>
#include "../type.h"

// Generate ON duration based on servo angle (0-180 degrees)
void waitServoOnPulse(u16 angle);
// Generate OFF duration based on servo angle
void waitServoOffPulse(u16 angle);

#endif 