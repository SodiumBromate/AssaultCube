#include <windows.h>
#include <iostream>
#include "functions.h"

bool bSpeed = false;

void speed(HANDLE hProc, std::vector <unsigned int> velocityAddr)
{
	if (GetAsyncKeyState(0x4D) & 1)
	{
		bSpeed = !bSpeed;

		std::cout << "Sanik mode!\n";
	}
	if (bSpeed)
	{
		for (int i = 0; i < 3; i++)                                                                       //(i know the speedhack is pretty weird but its my first attempt at it)
		{
			float SpeedValue = 0;
			ReadProcessMemory(hProc, (BYTE*)velocityAddr[i], &SpeedValue, sizeof(SpeedValue), 0);         //reads the velocity value of all 3 addresses
			float OldSpeedValue = SpeedValue / 2.1;                                                       //divides the old speed value by 2.1
			float newSpeedValue = OldSpeedValue * 3;                                                      //multiplies the new speed value by 3 making you go slightly faster
			mem::PatchEx((BYTE*)velocityAddr[i], (BYTE*)&newSpeedValue, sizeof(newSpeedValue), hProc);    //assigns the new value to all 3 addresses
			Sleep(20);
			
		}                                                                                                 //modifying the 2.1 may send you into hyperdrive (you have been warned!)
	}
}