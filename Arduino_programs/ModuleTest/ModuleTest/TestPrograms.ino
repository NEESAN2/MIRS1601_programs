/*
�e��e�X�g�v���O����������t�@�C��
*/
#include "Arduino.h"
#include "PinAssignment.h"

/*
�e�N���X�̎���
TODO:�N���X�̎���
*/

class Program
{
public:
	//�������\�b�h
	void Processor()
	{
		//���ʕ����ł���while�Amenu()�Acommand���L�q
		while (true)
		{
			readSerialEnd();
			if (isEnd)
			{
				goto END;
			}
			else {
				//process()�͏������z�֐��ŁA���̃N���X�ɂ͎�������Ă��Ȃ�
				process();
			}
		}
	END:
		isEnd = false;
		menu();
	}
	void readSerialEnd()
	{
		if (Serial.read() == 'e') {
			isEnd = true;
		}
	}

protected:
	//���̊֐����I�[�o�[���C�h���邱�ƂŁA�q�N���X(�e�e�X�g�v���O����)�ɂ���ď�����ς�����
	virtual void process() = 0;

private:
	bool isEnd = false;
};

class Motor : public Program
{
public:
	Motor() {};

	void process()
	{

	}
};

class Uss : public Program
{
public:
	Uss() {};
	void process()
	{

	}
};

class Ir : public Program
{
public:
	Ir() {};
	void process()
	{

	}
};

class Tape : public Program
{
public:
	Tape() {};
	void process()
	{
		count++;
		ledFlashBinary();
		delay(1000);
		count = count >= 8 ? 0 : count;
	}
private:
	int count;
	int pins[3] = { TL_0,TL_1,TL_2 };

	void ledFlashBinary()
	{
		int i, j;
		byte state;
		for (i = 0, j = 1; i < sizeof(pins) / sizeof(pins[0]); i++, j = j * 2)
		{
			//����()�͏d�v�B�Ȃ��Ƌ��������������Ȃ�B
			state = (count & j) > 0 ? HIGH : LOW;
			digitalWrite(pins[i], state);
		}
	}
};

class Encoder : public Program
{
public:
	Encoder() {};
	void process()
	{

	}
};

class Mp3 : public Program
{
public:
	Mp3() {};
	void process()
	{

	}
};

//�q�N���X���C���X�^���X��
//����ŐV�����N���X���ł��Ă��ύX���y
Program *pTests[5] = { new Motor, new Uss, new Ir, new Encoder, new Mp3 };

void selector() {
	//�R�}���h�̕����ɂ���Ďq�N���X�̃|�C���^��e�N���X�֑��
	switch (command)
	{
	case 'm':
		pTests[0]->Processor();
		break;

	case 'u':
		pTests[1]->Processor();
		break;

	case 'i':
		pTests[2]->Processor();
		break;

	case 't':
		pTests[3]->Processor();
		break;

	case 'e':
		pTests[4]->Processor();
		break;

	case 'M':
		pTests[5]->Processor();
		break;

	default:
		//�Ȃɂ��������Ȃ�
		break;
	}
	command = NULL;
}
