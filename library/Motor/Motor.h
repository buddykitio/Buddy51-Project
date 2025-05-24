#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <8052.h>
#include "../type.h"

void waitServoPulse(u16 angle, u8 isOff);

#define SERVO_ON 0
#define SERVO_OFF 1

#endif 