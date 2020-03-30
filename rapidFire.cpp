#include <windows.h>
#include <iostream>
#include "functions.h"


bool bFireRate = false;

void fireRate(uintptr_t fireRateAddr, HANDLE hProcess)
{
	if (GetAsyncKeyState(0x4C) & 1)
	{
		bFireRate = !bFireRate;

		std::cout << "Rapid Fire!\n";
	}
	if (bFireRate)
	{
		mem::PatchEx((BYTE*)fireRateAddr, (BYTE*)&shootSpeed, sizeof(shootSpeed), hProcess);      //assigns a new fire rate to the current one
	}
}