// Recitation 3
// By: Rafael Rodriguez - mat574

#include <Windows.h>
#include <stdio.h>

unsigned char gArray[] = { 0x05, 0xFE, 0x1A, 0x1C, 0x28, 0xCC, 0xD3, 0x81 };
short int gArraySI[] = { 0x05, 0xFE, 0x1A, 0x1C, 0x28, 0xCC, 0xD3, 0x81 };
int gArrayI[] = { 0x05, 0xFE, 0x1A, 0x1C, 0x28, 0xCC, 0xD3, 0x81 };

int test()
{
	__asm {
		mov al, gArray
		lea esi, gArray
		mov dl, byte ptr [esi]
		mov edx, dword ptr [esi+2]
		mov al, gArray[5] 
		nop
		mov ax, gArraySI
		lea esi, gArraySI
		mov dl, byte ptr [esi]
		mov edx, dword ptr [esi+2]
		mov ax, gArraySI[5]
		mov eax, gArrayI
		lea esi, gArrayI
		mov dl, byte ptr [esi]
		mov edx, dword ptr [esi+2]
		mov eax, gArrayI[5]
	}
	return 0;
}

int main(int argc, char *argv[])
{
	test();
	exit(0);
}