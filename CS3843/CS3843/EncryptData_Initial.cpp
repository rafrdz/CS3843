// EncryptData.cpp
//
// This file uses the input data and key information to encrypt the input data
//

#include "Main.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// code to encrypt the data as specified by the project assignment
int encryptData(char *data, int dataLength)
{
	int resulti = 0;

	gdebug1 = 0;					// a couple of global variables that could be used for debugging
	gdebug2 = 0;					// also can have a breakpoint in C code

	int interator = 0;
	int starting_index = 0;
	// You can not declare any local variables in C, but should use resulti to indicate any errors
	// Set up the stack frame and assign variables in assembly if you need to do so
	// access the parameters BEFORE setting up your own stack frame
	// Also, you cannot use a lot of global variables - work with registers

	__asm {
		mov eax, gptrPasswordHash[0]
		shl eax,8 
		add eax, gptrPasswordHash[1]
		mov starting_index,eax

	LOOP1:
		mov eax, data[interator]
		xor eax, gptrKey[starting_index]
		mov data[interator],eax
		mov eax, interator
		sub eax,dataLength
		jne LOOP1
	
		
	}

	return resulti;
} // encryptData