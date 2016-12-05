/*
file   : BlinkLED_binary.cpp
Create : 2016/12/02
Author : R. Hirayama
Board  : Arduino Due

feture :
0~8�̐�����3bit��2�i���ɃG���R�[�h������A�e���ɑΉ�����LED�����点�܂��B
*/

#include "Arduino.h"
#include "BlinkLED_binary.h"

//�������q���X�g C++0x�ȍ~�łȂ��Ǝg���Ȃ��͗l
BlinkLED_binary::BlinkLED_binary(int LED1, int LED2, int LED3) : _LED{ LED1,LED2,LED3 }
{
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
}