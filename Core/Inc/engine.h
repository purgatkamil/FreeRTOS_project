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

void Engine(engine_state state);
void EnginesInit(GPIO_TypeDef* EN1_Port, uint16_t EN1_Pin, GPIO_TypeDef* EN2_Port, uint16_t EN2_Pin);
void EngineMoveForward();
void EngineMoveBackward();
void EngineStop();
void EngineTurnRight();
void EngineTurnLeft();


#endif /* INC_ENGINE_H_ */
