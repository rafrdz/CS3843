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
	int starting_index = gptrPasswordHash[0] * 256 + gptrPasswordHash[1];
	unsigned char lValue = gptrKey[starting_index];
	// You can not declare any local variables in C, but should use resulti to indicate any errors
	// Set up the stack frame and assign variables in assembly if you need to do so
	// access the parameters BEFORE setting up your own stack frame
	// Also, you cannot use a lot of global variables - work with registers

	__asm {
		mov ecx, dataLength    // Copy dataLength into ecx register
		test ecx, ecx    // Check if ecx is 0
		je ED_EXIT    // Exit if 0

		mov edi, data    // Copy data into edi register
		test edi, edi    // Check if edi is 0
		je ED_EXIT    // Exit if 0

		xor ebx,ebx
		xor eax,eax
		xor edx,edx

		mov ebx, gptrPasswordHash
		mov al, byte ptr[ebx] // Copy first byte of ebx into al
		shl al, 8 // Multiply by 256
		mov dl, byte ptr[ebx + 1] // Copy second byte of ebx into dl
		add al, dl // Add al and bl, store result in al

		xor edx,edx
		xor ebx,ebx

		mov edx,gptrKey
		mov bl, byte ptr[edx + eax] // Copy
		
		xor ecx, ecx    // Zero out ecx

	ED_LOOP:
		push ebp
		mov ebp, esp
		mov al, byte ptr[edi+ecx]    // Copy 1 byte of 'data' into al
		xor eax, ebx
		mov byte ptr[edi+ecx], al
		inc ecx
		cmp ecx, dataLength
		jne ED_LOOP

	ED_EXIT:
	}

	/*__asm {
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
	
		
	}*/

	return resulti;
} // encryptData