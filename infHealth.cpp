#include <windows.h>
#include <iostream>
#include "functions.h"


bool bHealth = false;

void infHealth(uintptr_t healthAddr, HANDLE hProcess)
{
	if (GetAsyncKeyState(0x48) & 1)
	{
		bHealth = !bHealth;

		std::cout << "Unlimited Health!\n";

	}

	if (bHealth)
	{
		mem::PatchEx((BYTE*)healthAddr, (BYTE*)&newValue, sizeof(newValue), hProcess);     //assign a new health value to the current one

	}
}