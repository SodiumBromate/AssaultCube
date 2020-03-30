#include "Proc.h"

DWORD GetProcID(const wchar_t* procNAME)
{
	DWORD procID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //TH32CS_SNAPPROCESS creates a snapshot of all running processes and stores the handle in hSnap
	if (hSnap != INVALID_HANDLE_VALUE)                              //if TH32CS_SNAPPROCESS fails, it will give you INVALID_HANDLE_VALUE as a return
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))                      //Gets first running process ID and stores it in procEntry
		{

			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procNAME))       //compares the procID it has with procNAME using string compare
				{                                                   //once process is found, it will break out of the do while loop
					procID = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));



		}
	}
	CloseHandle(hSnap);                                             //stop memory leaks
	return procID;                                                  //return processID
}
                                                                                                     //_
uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName)                                 // |
{                                                                                                    // |
	uintptr_t modBaseAddr = 0;                                                                       // |
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);        // | <- you also use procID instead of 0 here
	if (hSnap != INVALID_HANDLE_VALUE)                                                               // |
	{                                                                                                // |
		MODULEENTRY32 modEntry;                                                                      // |
		modEntry.dwSize = sizeof(modEntry);                                                          // |
																									 // |
		if (Module32First(hSnap, &modEntry));                                                        // |
		{                                                                                            // |
			do                                                                                       // | exactly the same as the function above just intead of getting procID
			{                                                                                        // | its gettting the Module Base Address
				if (!_wcsicmp(modEntry.szModule, modName))                                           // |
				{                                                                                    // |
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;                                   // |
					break;                                                                           // |
				}                                                                                    // |
			} while (Module32Next(hSnap, &modEntry));                                                // |
																									 // |
		}                                                                                            // |
	}                                                                                                // |
	CloseHandle(hSnap);                                                                              // |
	return modBaseAddr;                                                                              // |
}                                                                                                    //_|

uintptr_t findDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;                                                                            //grabs the value of ptr and assigns it to the variable addr
	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];                                                                          //add the address it has just found to the vector 
	}
	return addr;
}
