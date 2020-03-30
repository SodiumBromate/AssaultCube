#include <iostream>
#include <vector>
#include <windows.h>
#include "functions.h"


int main()
{

	std::vector <unsigned int> fireRateOffsets = { 0x374, 0xC, 0x10A };

	DWORD procID = GetProcID(L"ac_client.exe");

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

	uintptr_t moduleBase = GetModuleBaseAddress(procID, L"ac_client.exe");

	uintptr_t localPlayerPtrBase = moduleBase + 0x10F4F4;                                        //static address for the local player

	uintptr_t healthAddr = findDMAAddy(hProcess, localPlayerPtrBase, { 0xF8 });                  // no need to define vector separately as its just one offset

	uintptr_t fireRateAddr = findDMAAddy(hProcess, localPlayerPtrBase, fireRateOffsets);         //address for current guns fire rate

	uintptr_t velocityZAddr = findDMAAddy(hProcess, localPlayerPtrBase, { 0x18 });               // 0x18 offset for the z velocity

	uintptr_t velocityXYAddr = findDMAAddy(hProcess, localPlayerPtrBase, { 0x14 });              // 0x14 offset for the x or y velocity (depends on orientation)

	uintptr_t velocityYXAddr = findDMAAddy(hProcess, localPlayerPtrBase, { 0x10 });              // 0x10 offset for the x or y velocity (depends on orientation)

	std::vector <unsigned int> velocityAddr = {velocityZAddr, velocityXYAddr, velocityYXAddr};   //vector of all the velocity addresses (makes them easier to work with)

	std::cout << "Process Handle: " << hProcess << "\n";                                         //prints process handle
	std::cout << "Process ID: " << procID << "\n" << "\n";                                       //prints process id

	std::cout << "Sodium's Cheeto\n"
		<< "---------------------------------------------\n"
		<< "Press H for Infinite Health\n"
		<< "Press J for Infinite Ammo\n"
		<< "Press K for No-recoil\n"                                                             //quick console menu
		<< "Press L for Rapid Fire!\n"
		<< "Press M for Sanik Mode!\n"
		<< "---------------------------------------------\n";


	if (!procID)                                                                                 //if procID is not found then go into the loop
	{
		std::cout << "Process not found! Press enter to close\n";
		(void)getchar();                                                                         //dont need to worry because we dont need return value
		return 0;
	}
	

	DWORD terminStatus = 0;

	while (GetExitCodeProcess(hProcess, &terminStatus) && terminStatus == STILL_ACTIVE)
	{
		infHealth(healthAddr, hProcess);                                                         //health function (infHealth.cpp)

		infAmmo(hProcess, moduleBase);                                                           //ammo function (infAmmo.cpp)
        
		noRecoil(hProcess, moduleBase);                                                          //recoil function(noRecoil.cpp)

		fireRate(fireRateAddr, hProcess);                                                        //fire rate function(rapidFire.cpp)

		speed(hProcess, velocityAddr);                                                           //speed function(speed.cpp)

		if (GetAsyncKeyState(VK_INSERT) & 1)                                                     //if you press INS the cheat will stop and close
		{
			std::cout << "Cheat closed\n";
			return 0;
		}


		Sleep(10);
	}
	
	std::cout << "Process not found, press enter to exit\n";
    (void)getchar(); //dont need to worry because we dont need return value
    return 0;
}


