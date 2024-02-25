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


void EnginesInit(){
	HAL_TIM_Base_Start(&htim4);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	EnginesSetSpeed(100, 100);
}

void EnginesSpeed(engine_speed engine_speed){
	static int speed = 100;

	switch (engine_speed){
		case KEEP:
			speed = speed;
			break;
		case FASTER:
			if(speed < 100)
				speed += 10;
			break;
		case SLOWER:
			if(speed > 50)
				speed -= 10;
			break;
	}

	EnginesSetSpeed(speed, speed);
}

void EnginesSetSpeed(uint8_t speedLeft, uint8_t speedRight){
	if(speedLeft >= htim4.Instance->ARR){
		speedLeft = htim4.Instance->ARR;
	}
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, speedLeft);

	if(speedRight >= htim4.Instance->ARR){
		speedRight = htim4.Instance->ARR;
	}
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, speedRight);
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
