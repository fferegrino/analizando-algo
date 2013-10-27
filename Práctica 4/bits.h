/* 
 * File:   bits.h
 * Author: fferegrino
 *
 * Created on 25 de octubre de 2013, 04:15 PM
 */

#ifndef __BITS_H__
#define	__BITS_H__

#define PESOBIT(bpos) 1<<bpos
#define COGEBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)
#define BYTE 8

void pon1(char * array, int pos){
	int ix = pos / BYTE;
	int i = pos - (BYTE * ix);
	i =  BYTE - i - 1;
	PONE_1(array[ix],i);
}

void pon0(char * array, int pos){
	int ix = pos / BYTE;
	int i = pos - (BYTE * ix);
	i =  BYTE - i - 1;
	PONE_0(array[ix],i);
}
	

#endif	/* __BITS_H__ */