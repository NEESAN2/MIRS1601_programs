/*
 * USART_ver1.h
 *
 *    Created: 2014/02/17 8:26:02
 * LastUpdate: 2015/06/18 21:30:00
 *     Author: Shunya.Iida
 *       Type: ATmega328P family
 *    Version: 1.1
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#ifndef UsartReadMax
#define UsartReadMax 10
#endif


#if UsartReadMax>200
#error "UsartReadMax�̒l���傫�����܂�"
#endif


#ifndef USART_VER_1_H
#define USART_VER_1_H

uint8_t Usart_Init(uint8_t baudratemode,uint16_t baudrate);
void Usart_Begin(void);
void Usart_End(void);
void Usart_Write(uint8_t writedata);
uint8_t Usart_Read (uint8_t *_readdata);
uint8_t Usart_ReadDataBaff(uint8_t *_readdata,uint8_t _mode);
uint8_t Usart_Available(void);

uint8_t Usart_Init(uint8_t baudratemode,uint16_t baudrate){
	
	UCSR0A=0x00;
	UCSR0B=0x00;
	UCSR0C=0x00;
	if(baudrate>0x0FFF){
		return 0xFE;
	}
	switch(baudratemode){
	case 1: UCSR0A=(_BV(U2X0));
			break;
	case 0: break;
	default: return 0xFF;
				break;
	}
	UBRR0=baudrate;
	UCSR0C=(_BV(UCSZ01) | _BV(UCSZ00) );
	UCSR0B=_BV(RXCIE0);
	return 0;
}

void Usart_Begin(void){
	UCSR0B|=( _BV(RXEN0) | _BV(TXEN0) );
}

void Usart_End(void){
	while( !(UCSR0A & _BV(UDRE0)));
	UCSR0B&=~( _BV(RXEN0) | _BV(TXEN0) );
}

uint8_t Usart_Read (uint8_t *_readdata){
	
	uint8_t _mode;
	uint8_t i;
	_mode=Usart_ReadDataBaff(&i,1);
	*_readdata=i;
	Usart_Write(i);
	return _mode;
}

void Usart_Write(uint8_t _writedata){
	while( !(UCSR0A & _BV(UDRE0))){;}
	UDR0=_writedata;
}

uint8_t Usart_Available(void){
	uint8_t i;
	return Usart_ReadDataBaff(&i,2);
}

uint8_t Usart_ReadDataBaff(uint8_t *_readdata,uint8_t _mode){
	
	static uint8_t _buffamout=0;
	static uint8_t UsartReadDataBaffer[UsartReadMax];

	uint8_t _usart_output=0;
	uint8_t i;
	
	if(_mode==0){		//�������݃��[�h
		if(UsartReadMax>_buffamout){
			UsartReadDataBaffer[_buffamout]=*_readdata;
		}else{
			for(i=0;i<UsartReadMax;i++){
				UsartReadDataBaffer[i]=UsartReadDataBaffer[i+1];
			}
			UsartReadDataBaffer[UsartReadMax-1]=*_readdata;
		}
		_buffamout++;
		
	}else if(_mode==1){		//�ǂݍ��݃��[�h
		if(_buffamout<=0){
			_buffamout=0;
			_usart_output=0;
		}else{
			*_readdata=UsartReadDataBaffer[0];
			_usart_output=_buffamout;
			if(_buffamout<UsartReadMax){	//ReadData���I�[�o�[�t���[���Ă��Ȃ��Ƃ�
				for(i=0;i<_buffamout;i++){	
					UsartReadDataBaffer[i]=UsartReadDataBaffer[i+1];
				}
			}
			else{		//�I�[�o�[�t���[���Ă���܂��͂҂�����̂Ƃ�
				_buffamout=UsartReadMax-1;
				for(i=1;i<_buffamout;i++){
					UsartReadDataBaffer[i-1]=UsartReadDataBaffer[i];
				}
			}
			_buffamout--;
		}
	}
	else if(_mode == 2){ //�m�F���[�h
		_usart_output = _buffamout;
	}
	return _usart_output;
}

ISR(USART_RX_vect){
	uint8_t _Usart_UDR;
	_Usart_UDR=UDR0;
	Usart_ReadDataBaff(&_Usart_UDR,0);
}

#endif

/*********************************************************
 Copyright (c) 2014-2015  Shunya Iida
 All rights reserved.
 
 �{�v���O�����͏�L�̎�(�ȉ��u����ҁv�Ƃ����B)�ɂ���Đ��삳��Ă��܂��B
 �{�v���O������
  �E����҂��{�v���O�����ɂ�����S�Ă̍s�ׁA���Q�ɂ��Ĉ�؂̐ӔC�𕉂�Ȃ�����
  �E���ό�̃v���O�����ɂ�����҂���іƐӎ������܂߂邱��
  �E���ώ҂͏�L�̒���҂ɖ����L������
 ��L2�_�������ɖ{�v���O�����̎g�p�A�����A���ρA�Еz�A��������
 ��؂̍s�ׂ𖳒f�ōs�����Ƃ�F�߂܂��B
 *******************************************************/

