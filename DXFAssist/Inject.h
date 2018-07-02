#pragma once
#include <windows.h>
#include "Handle.h"
#include <math.h>

/* for test you can use this code in you program
DWORD  MyFunc(LPVOID pData)
{

	return *(DWORD*)pData * 2;
}

void AfterMyFunc(void)
{

}
DWORD cbCodeSize = abs((LPBYTE)AfterMyFunc - (LPBYTE)MyFunc);
*/

void InjectCreateThreadRunAsm(HANDLE processHandle, LPVOID asmfun, DWORD cbCodeSize) 
{
	PDWORD  startAddress = (PDWORD)VirtualAllocEx(processHandle, NULL, cbCodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (startAddress == NULL)
	{
		printf("virtualAllocEx error!");
		return;
	}
	BOOL result = WriteProcessMemory(processHandle, startAddress, asmfun, cbCodeSize, NULL);
	if (result == 0)
	{
		printf("Write ProcessMemory failed");
	}
	HANDLE hThread = CreateRemoteThread(processHandle, NULL, 0,
		(LPTHREAD_START_ROUTINE)startAddress,//
		NULL, 0, NULL);



	/*
	if (VirtualFreeEx(processHandle, startAddress, 0, MEM_RELEASE) == 0)
	{
		printf("VitualFreeEx error\n");
	}
	*/
}

void InjectCreateThreadRunFun(HANDLE processHandle, LPVOID fun,DWORD cbCodeSize)
{

	BOOL result = 0;
	char szBuffer[10];
	*(DWORD*)szBuffer = 1000; //for test
	DWORD cbParaSize = sizeof(szBuffer);

	PDWORD  startAddress = (PDWORD)VirtualAllocEx(processHandle, NULL, cbCodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (startAddress == NULL)
	{
		printf("virtualAllocEx error!");
		return;
	}

	void *pDataRemote = (char*)VirtualAllocEx(processHandle, 0, cbParaSize, MEM_COMMIT, PAGE_READWRITE);
	result = WriteProcessMemory(processHandle, pDataRemote, szBuffer, cbParaSize, NULL);
	if (result == 0)
	{
		printf("Write ProcessMemory failed");
	}

	result = WriteProcessMemory(processHandle, startAddress, fun, cbCodeSize, NULL);
	if (result == 0)
	{
		printf("Write ProcessMemory failed");
	}

	HANDLE hThread = CreateRemoteThread(processHandle, NULL, 0,
		(LPTHREAD_START_ROUTINE)startAddress,//
		pDataRemote, 0, NULL);
	if (hThread)
	{
		WaitForSingleObject(hThread, INFINITE);
		DWORD retuncode;
		GetExitCodeThread(hThread, &retuncode);
		printf("run and return %d ", retuncode);
		CloseHandle(hThread);
	}


	if (VirtualFreeEx(processHandle, pDataRemote, 0, MEM_RELEASE) == 0)
	{
		printf("VitualFreeEx error\n");
	}

	if (VirtualFreeEx(processHandle, startAddress, 0, MEM_RELEASE) == 0)
	{
		printf("VitualFreeEx error\n");
	}
}