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

	// You can not declare any local variables in C, but should use resulti to indicate any errors
	// Set up the stack frame and assign variables in assembly if you need to do so
	// access the parameters BEFORE setting up your own stack frame
	// Also, you cannot use a lot of global variables - work with registers

	__asm {
		// Encrypt code by Team 6
		// Rafael Rodriguez, David Brenner, Jacob De Hoyos
		xor esi, esi
		xor edi, edi
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx

		mov esi, gptrKey

		mov edi, gptrPasswordHash

		movzx eax, byte ptr[edi] // Get first byte of password hash
		shl eax, 8 // Multiply first byte of password hash by 256
		movzx ebx, byte ptr[edi + 1] // Get second byte of password hash
		add eax, ebx // Sum the two bytes to get starting_index

		movzx edx, byte ptr[gkey + eax] // Get the gKey[starting_index] value
		mov esi, data

		xor ebx, ebx // Zero out ebx to use at the iterator value
		xor eax, eax // Zero out eax to use as xor temp value
		xor edi, edi // Zero out edi to store dataLength

		mov edi, dataLength
		dec edi // Decrement edi for 0-indexing

	ENC_LOOP:
		mov cl, byte ptr[esi + ebx] // Copy byte of data into al
		xor cl, dl // xor byte of data with gKey[starting_index]
		
		// D - Code Table Swap
		push edi
		lea edi, gEncodeTable
		movzx edi, byte ptr [edi+ecx]
		mov ecx, edi
		pop edi
		
		// E - Reverse Bit Order
		push ebx
		xor ebx,ebx
		mov  bl, 8
	
	REVERSE:
		shr ecx, 1
		rcl al, 1
		dec bl
		jne REVERSE
		mov ecx,eax
		xor ebx,ebx
		xor eax,eax
		pop ebx
		
		// A - Swap Even/Odd Bits
		mov eax, ecx
		shl eax ,1
		and eax , 0xAA
		shr ecx , 1
		and ecx, 0x55
		add ecx,eax
		xor eax,eax
		
		// C - Swap Nibbles
		push ebx
		xor ebx, ebx
		mov  bl, 4
	
	REVERSE_NIBBLE:
		shr ecx, 1
		rcr al, 1
		dec bl
		jne REVERSE_NIBBLE
		add ecx, eax
		xor ebx, ebx
		xor eax, eax
		pop ebx
		
		// B - Invert Middle 4 Bits
		xor ecx, 0x3C

		mov byte ptr[esi + ebx], cl // Copy al back into data
		inc ebx // Increment iterator
		cmp ebx, edi // Check if end of data
		je ENC_EXIT // End loop and exit
		jmp ENC_LOOP // Repeat loop

	ENC_EXIT:
	}
	return resulti;
} // encryptData