#include "engine.h"


void Engine(engine_state state){

	switch (state){
		case MOVE_FORWARD:
			EngineMoveForward();
			break;
		case TURN_RIGHT:
			EngineTurnRight();
			break;
		case MOVE_BACKWARD:
			EngineMoveBackward();
			break;
		case TURN_LEFT:
			EngineTurnLeft();
			break;
		case STOP:
			EngineStop();
			break;
		default:
			break;
	}
}


void EnginesInit(GPIO_TypeDef* EN1_Port, uint16_t EN1_Pin, GPIO_TypeDef* EN2_Port, uint16_t EN2_Pin){
    HAL_GPIO_WritePin(EN1_Port, EN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN2_Port, EN2_Pin, GPIO_PIN_SET);
}

void EngineMoveForward(){
    HAL_GPIO_WritePin(Engine_IN1_GPIO_Port, Engine_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Engine_IN3_GPIO_Port, Engine_IN3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Engine_IN2_GPIO_Port, Engine_IN2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Engine_IN4_GPIO_Port, Engine_IN4_Pin, GPIO_PIN_SET);
}

void EngineMoveBackward(){
	HAL_GPIO_WritePin(Engine_IN1_GPIO_Port, Engine_IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Engine_IN3_GPIO_Port, Engine_IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Engine_IN2_GPIO_Port, Engine_IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Engine_IN4_GPIO_Port, Engine_IN4_Pin, GPIO_PIN_RESET);
}

void EngineStop(){
	HAL_GPIO_WritePin(Engine_IN1_GPIO_Port, Engine_IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Engine_IN3_GPIO_Port, Engine_IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Engine_IN2_GPIO_Port, Engine_IN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Engine_IN4_GPIO_Port, Engine_IN4_Pin, GPIO_PIN_SET);
}

void EngineTurnRight(){
	HAL_GPIO_WritePin(Engine_IN1_GPIO_Port, Engine_IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Engine_IN3_GPIO_Port, Engine_IN3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Engine_IN2_GPIO_Port, Engine_IN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Engine_IN4_GPIO_Port, Engine_IN4_Pin, GPIO_PIN_SET);
}

void EngineTurnLeft(){
	HAL_GPIO_WritePin(Engine_IN1_GPIO_Port, Engine_IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Engine_IN3_GPIO_Port, Engine_IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Engine_IN2_GPIO_Port, Engine_IN2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Engine_IN4_GPIO_Port, Engine_IN4_Pin, GPIO_PIN_RESET);
}
