
#pragma once
#include "Inject.h"
static DWORD WINAPI  MyFunc(LPVOID pData)
{
	return *(DWORD*)pData * 2;
}
static void AfterMyFunc(void)
{

}

void TestInjectThread()
{
	AfterMyFunc();
	HANDLE htest = GetProcessHandleByName("TestApp.exe");

	HANDLE processHandle;
	processHandle = htest;

	DWORD cbCodeSize = abs((LPBYTE)AfterMyFunc - (LPBYTE)MyFunc);
	InjectCreateThreadRunFun(htest, MyFunc, 25);
}
