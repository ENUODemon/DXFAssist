#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <processthreadsapi.h>
#include <stdio.h>

int EnableDebugPriv(const  LPCSTR name)
{
	HANDLE hToken;   //�������ƾ��
	TOKEN_PRIVILEGES tp;  //TOKEN_PRIVILEGES�ṹ�壬���а���һ��������+��������Ȩ������
	LUID luid;       //�����ṹ���е�����ֵ
					 //�򿪽������ƻ�
					 //GetCurrentProcess()��ȡ��ǰ���̵�α�����ֻ��ָ��ǰ���̻����߳̾������ʱ�仯
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		printf("OpenProcessToken error\n");
		return -8;
	}
	//��ñ��ؽ���name�������Ȩ�����͵ľֲ�ΨһID
	if (!LookupPrivilegeValue(NULL, name, &luid))
	{
		printf("LookupPrivilegeValue error\n");
	}
	tp.PrivilegeCount = 1;    //Ȩ��������ֻ��һ����Ԫ�ء�
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  //Ȩ�޲���
	tp.Privileges[0].Luid = luid;   //Ȩ������
									//��������Ȩ��
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


