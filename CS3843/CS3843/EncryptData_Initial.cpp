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
		mov esi, gptrKey // Copy pointer to gKey to esi
		mov edi, gptrPasswordHash // Copy pointer to gPasswordHash to edi

		movzx eax, byte ptr[edi] // Get first byte of password hash
		shl eax, 8 // Multiply first byte of password hash by 256
		movzx ebx, byte ptr[edi + 1] // Get second byte of password hash
		add eax, ebx // Sum the two bytes to get starting_index

		movzx edx, byte ptr[gkey + eax] // Get the gKey[starting_index] value
		mov esi, data // Copy data to esi

		xor ebx, ebx // Zero out ebx to use at the iterator value
		xor eax, eax // Zero out eax to use as xor temp value
		xor edi, edi // Zero out edi to use for dataLength

		mov edi, dataLength
		dec edi // Decrement edi for zero-index

	ENC_LOOP:
		movzx ecx, byte ptr[esi + ebx] // Copy byte of data into ecx
		xor ecx, edx // xor byte of data with gKey[starting_index]

		/*// D - Code Table Swap
		push edi // Push "dataLength - 1" to the stack
		lea edi, gDecodeTable // Move address of gDecodeTable to edi
		movzx edi, byte ptr [edi + ecx]
		mov ecx, edi
		pop edi*/

		// E - Reverse Bit Order
		push ebx // Push iterator to the stack
		mov ebx, 8 // Set the reverse loop counter

	REVERSE:
		shr ecx, 1
		rcl eax, 1
		dec ebx
		jne REVERSE
		mov ecx, eax
		xor ebx, ebx
		xor eax, eax
		pop ebx

		// A - Swap Even/Odd Bits
		mov eax, ecx // Copy value to eax
		shl eax, 1 // Shift left by 1
		and eax, 0xAA // And value by 0xAA
		shr ecx, 1 // Shift right by 1
		and ecx, 0x55 // And value by 0x55
		add ecx, eax // Add values together and store in ecx
		xor eax, eax // Zero out eax

		// C - Swap Nibbles
		push ebx // Push ebx to stack
		xor ebx, ebx // Zero out ebx
		mov eax, ecx // Copy value to eax
		and eax, 0x0F // And eax with 0x0F to zero out all but last 4 bits
		shl eax, 4 // Shift left by 4 to make the new last 4 bits 0
		mov ebx, ecx // Copy value to ebx
		and ebx, 0xF0 // And ebx with 0xF0 to zero out all but first 4 bits
		shr ebx, 4 // Shift right by 4 to make the new first 4 bits 0
		or eax, ebx // Or the two registers to swap the nibbles
		mov ecx, eax // Copy result into value
		xor eax, eax // Zero out eax
		pop ebx // Pop ebx off of the stack

		// B - Invert Middle 4 Bits
		xor ecx, 0x3C // xor value with 0x3C to invert middle 4 bits

		mov byte ptr[esi + ebx], cl // Copy cl back into data
		cmp ebx, edi // Check if end of data
		je ENC_EXIT // End loop and exit
		inc ebx // Increment iterator
		jmp ENC_LOOP // Repeat loop

	ENC_EXIT:
	}
	return resulti;
} // encryptData