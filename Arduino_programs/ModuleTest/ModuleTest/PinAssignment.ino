/*
�s���̏�����������t�@�C��
*/
#include "Arduino.h"
#include "PinAssignment.h"

//�������֐���`
void initPinAssiment(const int Pins[], byte io) {
	for (int i = 0; i < sizeof(Pins) / sizeof(Pins[0]); i++)
	{
		pinMode(Pins[i], io);
	}
}