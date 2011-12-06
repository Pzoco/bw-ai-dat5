// isAlive.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

#include <tlhelp32.h>
using namespace std;
DWORD FindProcessId(const std::wstring& processName);


void KillProcess(DWORD pid)
{
	HANDLE	tokenHandle = INVALID_HANDLE_VALUE;
	TOKEN_PRIVILEGES	newTokenPrivileges;
	TOKEN_PRIVILEGES	oldTokenPrivileges;
	DWORD	 oldTokenPrivilegeSize = 0;
	LUID	newLuid;

	// Get Debug Privileges for current process
	if(!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &tokenHandle))
	{
		cout << "Unable to get current process token -  " << GetLastError() << std::endl;
		return;
	}

	// Get the LUID for SE_DEBUG_NAME
	if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &newLuid))
	{
		cout << "Unable to lookup privilege value SE_DEBUG_NAME - " << GetLastError() << std::endl;
		return;
	}

	// Setup new token privileges
	newTokenPrivileges.PrivilegeCount = 1;	// We need only one privilege to change time
	// Copy over privilege value to one which we will send to system
	memcpy(&newTokenPrivileges.Privileges[0].Luid, &newLuid, sizeof(LUID)); // The privilege to change system time
	newTokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Enable it !!

	// Adjust the process token privileges
	if(!AdjustTokenPrivileges(tokenHandle, FALSE, &newTokenPrivileges, sizeof(TOKEN_PRIVILEGES), &oldTokenPrivileges, &oldTokenPrivilegeSize))
	{
		cout << "Unable to adjust token privileges for current process - " << GetLastError() << std::endl;
		return;
	}

	HANDLE processHandle = OpenProcess (PROCESS_ALL_ACCESS, 0, pid);

	if (!processHandle)
	{
		cout << "Could not get process andle for " << GetLastError() << "... error = " << GetLastError() <<std::endl;
	}

	if (!TerminateProcess(processHandle, 0))
	{
		cout << "Could not terminate process " << pid << "... error = " << GetLastError() <<std::endl;
	}

	CloseHandle(processHandle);
}


int _tmain(int argc, _TCHAR* argv[])
{
	while(true)
	{

		time_t now; 
		time(&now); 
		unsigned int uiNow = static_cast <unsigned int> (now); 

		std::ifstream file("C:/lastGame.txt"); 
		std::string line; 
		long int timeFromFile;
		std::getline(file,line);
		timeFromFile = atol(line.c_str()); 
		file.close(); 
	
		long int diff = (uiNow - timeFromFile);
		if(diff > 10)
		{	
			cout << "TimeOut: "<< diff << "sec." << endl;

			//Getting process id
			std::wstring processName(L"StarCraft.exe");
			std::wstring processName2(L"Chaoslauncher.exe");
			DWORD pid = FindProcessId(processName);
			DWORD pid2 = FindProcessId(processName2);
			//Killing
			KillProcess(pid);
			KillProcess(pid2);
			
			//Starting Chaoslauncher
			WinExec("C:\\StarCraft\\Chaoslauncher\\Chaoslauncher.exe",SW_SHOW);

			//Emulating keyboard to start starcraft
			Sleep(1000);
			keybd_event(VkKeyScan('\n'),0,0,0);
			// s e \n u up up up up up up \n \n \n
			Sleep(1000);
			keybd_event(VkKeyScan('s'),0,0,0);
			Sleep(1000);
			keybd_event(VkKeyScan('e'),0,0,0);
			Sleep(1000);
			keybd_event(VkKeyScan('\n'),0,0,0);
			Sleep(1000);
			keybd_event(VkKeyScan('u'),0,0,0);
			Sleep(1000);
			keybd_event(VkKeyScan('\n'),0,0,0);
			Sleep(1000);
			keybd_event(VkKeyScan('\n'),0,0,0);
			Sleep(1000);
			keybd_event(VkKeyScan('\n'),0,0,0);
			Sleep(1000);
			keybd_event(VkKeyScan('\n'),0,0,0);
		}
			
		
		Sleep(2000); //Message Sleep for X ms
	}
	return 0;
}

DWORD FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if ( processesSnapshot == INVALID_HANDLE_VALUE )
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if ( !processName.compare(processInfo.szExeFile) )
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while ( Process32Next(processesSnapshot, &processInfo) )
	{
		if ( !processName.compare(processInfo.szExeFile) )
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}
	
	CloseHandle(processesSnapshot);
	return 0;
}