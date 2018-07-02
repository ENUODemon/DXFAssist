#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <processthreadsapi.h>
#include <stdio.h>

int EnableDebugPriv(const  LPCSTR name)
{
	HANDLE hToken;   //进程令牌句柄
	TOKEN_PRIVILEGES tp;  //TOKEN_PRIVILEGES结构体，其中包含一个【类型+操作】的权限数组
	LUID luid;       //上述结构体中的类型值
					 //打开进程令牌环
					 //GetCurrentProcess()获取当前进程的伪句柄，只会指向当前进程或者线程句柄，随时变化
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		printf("OpenProcessToken error\n");
		return -8;
	}
	//获得本地进程name所代表的权限类型的局部唯一ID
	if (!LookupPrivilegeValue(NULL, name, &luid))
	{
		printf("LookupPrivilegeValue error\n");
	}
	tp.PrivilegeCount = 1;    //权限数组中只有一个“元素”
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  //权限操作
	tp.Privileges[0].Luid = luid;   //权限类型
									//调整进程权限
	if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		printf("AdjustTokenPrivileges error!\n");
		return -9;
	}
	return 0;

}



HANDLE GetProcessHandleByName(LPSTR lpName)
{

	HANDLE processHandle = { 0 };
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
	{
		return NULL;
	}
	PROCESSENTRY32 pe = { sizeof(pe) };
	BOOL fOk;
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
	{
		if (!strcmp(pe.szExeFile, lpName)) //equal return 0
		{
			CloseHandle(hSnapshot);
			if (EnableDebugPriv(SE_DEBUG_NAME))
			{
				printf("Add Privilege error\n");
				return NULL;
			}
			processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
			return processHandle;
		}
	}
	return NULL;
}


