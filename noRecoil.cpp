#include <windows.h>
#include <iostream>
#include "functions.h"

bool bRecoil = false;

void noRecoil(HANDLE hProcess, uintptr_t moduleBase)
{
	if (GetAsyncKeyState(0x4B) & 1)
	{
		bRecoil = !bRecoil;

		std::cout << "No recoil!\n";

		if (bRecoil)
		{
			mem::NopEx((BYTE*)(moduleBase + 0x63786), 10, hProcess);                                                      // gets rid of the bytes that call the recoil function
		}
		else
		{
			mem::PatchEx((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10, hProcess); // replaces the bytes 
		}                                                                                                                
	}
}