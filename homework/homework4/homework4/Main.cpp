#include <Windows.h>
#include <stdio.h>

int test()
{
	__asm {
		push 0x12ff0
		push 0x00001
		push 0x00002
		push 0x00003
	}
}

int main(int argc, char *argv[])
{
	test();
	return 0;
}