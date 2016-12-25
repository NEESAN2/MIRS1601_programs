
			Remadme  USART_ver1_328P

 ���̕��͂�USART_ver1.h�̎g�������L���Ă�����̂ł��B�܂��A����
������AtmelStudio���g�p���ēǂނ��Ƃ𐄏��������܂��B

�Ή��}�C�R��:ATmega48A,ATmega88A,ATmega168A,ATmega328�y�т����
			 �}�C�R���̔h��



�֐��̈ꗗ�Ɩ����A���l

uint8_t Usart_Init(uint8_t baudratemode,uint16_t baudrate)
	�EUsart�Ɏg�p����|�[�g�ƒʐM���x�̎w��E������
		����	uint8_t  baudratemode �c�ʐM���[�h(2�{��or�ʏ�)
				uint16_t baudrate	  �c�{�[���[�g�l(UBRR�l)
		�߂�l	0		�ʏ�I��
				0xFF	baudratemode�l�̃G���[
				0xFE	baudrate�l�̃G���[
	��baudratemode,baudrate�̒l�͉��L�ɏ]���Ă��������B


void Usart_Begin(void)
	�EUsart�ʐM�̊J�n


void Usart_End(void)
	�EUsart�ʐM�̏I��
	���|�[�g�̕������W�X�^�ɏo�͂��ˑ�����̂ŁA�Z�����Ȃ��悤
	  �����Ӊ������B���̂��߁A�g�p���Ȃ����Ƃ𐄏����܂��B


void Usart_Write(uint8_t writedata)
	�EUsart�ʐM�ɂ��f�[�^���M(1Byte)
	�@�@����	uint8_t writedata	�c���M�f�[�^
	���M�f�[�^��1Byte��uint8_t�^(unsigned char�^)�ł��邱�ƁB
	�O��̑��M���I����Ă��Ȃ��ꍇ�A�I���܂őҋ@����B


uint8_t Usart_Read (uint8_t *_readdata)
	�EUsart��M�f�[�^�̓ǂݎ��
	�@�@����	uint8_t *_readdata   �c��M�f�[�^
		�߂�l�c��M�f�[�^�o�b�t�@�Ɋi�[����Ă���f�[�^��
				(��M�����f�[�^���܂񂾐�)
		���߂�l��0�̏ꍇ�A��M�f�[�^���Ȃ����Ƃ��Ӗ����܂��B
		�@���̂Ƃ��A�����̒��̃f�[�^��0(0x00)�ɂȂ�܂��B


uint8_t Usart_ReadDataBaff(uint8_t *_readdata,uint8_t _mode)
	�EReadData�o�b�t�@�̐���
	���֐����ł̂ݎg�p���܂��B��{�I�ɊO������Ăяo�������Ȃ���
	���������B




���ӎ����E���ӎ���
	�E��M�f�[�^���o�b�t�@�Ɉڂ��ۂɊ��荞�݂��g�p���Ă��܂��B
	�@��M����ۂ͑S���荞�݋���^���Ă��������B
	�EF_CPU�l��^���Ă��������B
	�E��M�f�[�^�o�b�t�@�̑傫����UsartReadMax(�}�N��)�ŗ^����
	  ���������B�o�b�t�@���傫���قǃI�[�o�[�t���[����\����
	  ����܂����A�������𑽂��g���܂��B�������A200���ő�l�ł��B
	  �܂��A�w�肳��Ȃ��ꍇ�E�f�t�H���g�l��10�ł��B
	�EUsart_Read�̎�M�f�[�^��'uint8_t *'�^�ł��B�|�C���^���Q��
	�@���Ă���̂Œ��ӂ��Ă��������B
	�E�I�[�o�[�t���[�����ꍇ�A�Â��f�[�^��������V�����f�[�^������܂��B


baudratemode,baudrate�̒l�ɂ���
	baudratemode�l�Abaudrate�l�͒ʐM���x��ݒ肷��ׂ̒l�ł��B
	baudratemode�l�c�{�����[�h�̐ݒ�
					�ʏ�(U2X=0)�c0
					�{��(U2X=1)�c1
	baudrate�l�cUBRR�l(CPU�N���b�N�̕����l)
		��uint16_t�^(unsigned short int)�ł��B�����ӂ��������B

	���l�̋��ߕ�
	1.���L�̕\���狁�߂�
		 	 �\1:��\�I�ȃN���b�N�̃{�[���[�g�l
   +-----------+------------+---------------+-----------+
   |  �X�s�[�h | CPU�N���b�N| baudratemode�l| baudrate�l|
   +-----------+------------+---------------+-----------+
   |  LowSpeed |      20MHz |          0    |      129  |
   |  (9600bps)|      16MHz |          0    |      103  |
   |           |       8MHz |          0    |       51  |
   |           |       1MHz |          1    |       42  |
   +-----------+------------+---------------+-----------+
   |MiddleSpeed|      20MHz |          1    |       64  |
   | (38400bps)|      16MHz |          0    |       25  |
   |           |       8MHz |          0    |       12  |
   +-----------+------------+---------------+-----------+
   | HighSpeed |      20MHz |          1    |        4  |
   |  (500kbps)|      16MHz |          0    |        1  |
   |           |       8MHz |          0    |        0  |
   +-----------+------------+---------------+-----------+

	2.�f�[�^�V�[�g��ǂ�
	�e�[�^�V�[�g�ɂ͑�\�I��CPU�N���b�N�ƒʐM���x�̑Ή��\���ڂ���
	���܂��B�܂��A�v�Z���������Ă���̂ł������狁�߂Ă��������B
	�\�ɂ͒ʏ�Ɣ{���̂Q��ނ̐��l�������Ă���܂����A�덷�̏�������
	���̗p���Ă��������B�덷���ԐF�̏ꍇ�A�M����������܂���B

	3.�t����C����̃\�[�X�v���O�������g�p����B
	�t�����Ă���v���O�����\�[�X�R�[�h���R���p�C�����A���삳���Ă��������B
	�덷�̌v�Z��������Ő��l��Ԃ��܂��B



�T���v���v���O����
������e:��M�����f�[�^�𑗐M����

/************************
 CPU�N���b�N�c20MHz
 �ʐM���x�cLowSpeed
 ��M�o�b�t�@�c10(Byte)
 ************************/

#define F_CPU 20000000UL		//CPU�c20MHz
#define UsartReadMax 10			//�o�b�t�@�̑傫����10�ɐݒ�
#include <avr/io.h>
#include <util/delay.h>
#include "USART_ver1.h"

int main(void){
	uint8_t a;
	uint8_t readdata;
	/*�|�[�g������*/
	DDRB=0x00;
	DDRC=0x00;
	DDRD=0x00;
	Usart_Init(0,129);			//USART�������E�{�[���[�g�l�ݒ�@
	_delay_ms(100);
	Usart_Begin();				//USART�ʐM�̋���
	sei();						//�S���荞�݋���
	Usart_Write(0xAA);			//0xAA�𑗐M(�ڑ��m�F�p)
	while(1){
		a=Usart_Read(&readdata);	//�f�[�^�ǂݎ��
		if(a>0){					//a>0����M�f�[�^������ꍇ
			Usart_Write(readdata);	//��M�f�[�^�𑗐M
		}
	}
	return 0;
}