#include <windows.h>
#include <iostream>
#include "functions.h"

bool bAmmo = false;

void infAmmo(HANDLE hProcess, uintptr_t moduleBase)
{
	if (GetAsyncKeyState(0x4A) & 1)
	{
		bAmmo = !bAmmo;

		std::cout << "Unlimited Ammo!\n";

		if (bAmmo)
		{
			mem::PatchEx((BYTE*)(moduleBase + 0x637E9), (BYTE*)"\xFF\x06", 2, hProcess); //when we find what accesses we end up on the address 0x637E9 and if you change dec [esi] to inc [esi]
		}                                                                                //the bytes go from FF 0E to FF 06 so we are changing the bytes to increment
		else
		{
			mem::PatchEx((BYTE*)(moduleBase + 0x637E9), (BYTE*)"\xFF\x0E", 2, hProcess);
		}
	}
}