/*
file   : BlinkLED_binary.h
Create : 2016/12/02
Author : R. Hirayama
Board  : Arduino Due

feture :
0~8�̐�����3bit��2�i���ɃG���R�[�h������A�e���ɑΉ�����LED�����点�܂��B
*/

#ifndef _TAPELED_h
#define _TAPELED_h

#include "Arduino.h"

class BlinkLED_binary
{
public:
	BlinkLED_binary(int LED1, int LED2, int LED3);

	void BlinkLED(int dec, int delayTime)
	{
		int i;
		int j;
		byte state;
		for (i = 0, j = 1; i < sizeof(this->_LED) / sizeof(this->_LED[0]); i++, j = j * 2)
		{
			//����()�͏d�v�B�Ȃ��Ƌ��������������Ȃ�
			state = (dec & j) > 0 ? HIGH : LOW;
			digitalWrite(this->_LED[i], state);
		}
		delay(delayTime);
	}

private:
	int _LED[3];
};

#endif

