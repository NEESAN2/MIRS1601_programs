/*
file   : L298N_omuni.cpp
Create : 2016/12/02
Author : R. Hirayama
Board  : Arduino Due
feture :
2��L298N��4�̃��[�^�[�𐧌䂵�܂��B
���炩���ߑO�㍶�E�A���E�΂ߑO�E���A���E���񂪊ȒP�ɏo����l�ɂȂ��Ă��܂��B
setupMotor�AdriveMotor�֐��𒼐ڎg�p���邱�ƂŁA���[�^�[���D���Ȃ悤�ɓ������܂��B
*/
#include "Arduino.h"
#include "L298N_omuni.h"

struct Motor
{
	int in1;
	int in2;
	int pwm;
};

Motor motors[4];

L298N_omuni::L298N_omuni(int A_ena, int A_in1, int A_in2, int A_in3, int A_in4, int A_enb,
	int B_ena, int B_in1, int B_in2, int B_in3, int B_in4, int B_enb)
{
	pinMode(A_ena, OUTPUT);
	pinMode(A_in1, OUTPUT);
	pinMode(A_in2, OUTPUT);
	pinMode(A_in3, OUTPUT);
	pinMode(A_in4, OUTPUT);
	pinMode(A_enb, OUTPUT);

	pinMode(B_ena, OUTPUT);
	pinMode(B_in1, OUTPUT);
	pinMode(B_in2, OUTPUT);
	pinMode(B_in3, OUTPUT);
	pinMode(B_in4, OUTPUT);
	pinMode(B_enb, OUTPUT);

	motors[0].in1 = A_in1;
	motors[0].in2 = A_in2;
	motors[0].pwm = A_ena;

	motors[1].in1 = A_in3;
	motors[1].in2 = A_in4;
	motors[1].pwm = A_enb;

	motors[2].in1 = B_in1;
	motors[2].in2 = B_in2;
	motors[2].pwm = B_ena;

	motors[3].in1 = B_in3;
	motors[3].in2 = B_in4;
	motors[3].pwm = B_enb;
}

/*
�k�A���𐳂Ƃ���
NSEW
N_in1,N_in2,S_in1,S_in2,E_in1,E_in2,W_in1,W_in2
*/
void L298N_omuni::forward(int speed, int delay_time)
{
	this->setupMotors(B00001010);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::backward(int speed, int delay_time)
{
	this->setupMotors(B00000101);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::right(int speed, int delay_time)
{
	this->setupMotors(B01010000);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::left(int speed, int delay_time)
{
	this->setupMotors(B10100000);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::rightForward(int speed, int delay_time)
{
	this->setupMotors(B01011010);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::leftForward(int speed, int delay_time)
{
	this->setupMotors(B10101010);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::rightBackward(int speed, int delay_time)
{
	this->setupMotors(B01010101);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::leftBackward(int speed, int delay_time)
{
	this->setupMotors(B10100101);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::turnRight(int speed, int delay_time)
{
	this->setupMotors(B10010110);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::turnLeft(int speed, int delay_time)
{
	this->setupMotors(B01101001);
	this->driveMotors(speed);
	delay(delay_time);
}

void L298N_omuni::fullStop(int delay_time)
{
	this->setupMotors(B00000000);
	this->driveMotors(0);
	delay(delay_time);
}


//������8�r�b�g�̓�i������́@char�����[�^��High Low����Ɋ��蓖�Ă��B
//0,1�r�b�g�ڂ��k�@2,3�r�b�g�ڂ���A4,5�r�b�g�ڂ����A6,7�r�b�g�ڂ���
void L298N_omuni::setupMotors(unsigned char& state)
{
	L298N_omuni::setupMotor(this->MOTOR_N, state & B1, state & B10);
	L298N_omuni::setupMotor(this->MOTOR_S, state & B100, state & B1000);
	L298N_omuni::setupMotor(this->MOTOR_E, state & B10000, state & B1000000);
	L298N_omuni::setupMotor(this->MOTOR_W, state & B1000000, state& B100000000);
}

void L298N_omuni::setupMotor(int motorIndex, int state1, int state2)
{
	digitalWrite(motors[motorIndex].in1, state1);
	digitalWrite(motors[motorIndex].in2, state2);
}

void L298N_omuni::driveMotors(int speed)
{
	this->driveMotor(this->MOTOR_N, speed);
	this->driveMotor(this->MOTOR_S, speed);
	this->driveMotor(this->MOTOR_E, speed);
	this->driveMotor(this->MOTOR_W, speed);
}
void L298N_omuni::driveMotor(int motorIndex, int speed)
{
	analogWrite(motors[motorIndex].pwm, speed);
}