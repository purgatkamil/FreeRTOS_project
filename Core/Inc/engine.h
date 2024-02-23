#include <string.h>
#include <stdio.h>
#include <usart.h>
#include <tim.h>
#include "ir.h"

#ifndef INC_ENGINE_H_
#define INC_ENGINE_H_

typedef enum {
	MOVE_FORWARD,
	MOVE_BACKWARD,
	TURN_RIGHT,
	TURN_LEFT,
	STOP
}engine_state;

typedef enum {
	KEEP,
	FASTER,
	SLOWER
}engine_speed;

void Engine(engine_state state);
void EnginesInit();
void EngineMoveForward();
void EngineMoveBackward();
void EngineStop();
void EngineTurnRight();
void EngineTurnLeft();
void EnginesSetSpeed(uint8_t speedLeft, uint8_t speedRight);
void EnginesSpeed(engine_speed engine_speed);


#endif /* INC_ENGINE_H_ */
