#pragma once
#include "Call.h"
#include "BaseAddress.h"
#include <Windows.h>
#include "Inject.h"


void __declspec(naked) fun()
{
	__asm {
		mov eax, [esp];
		ret;
	}
}

void TestCALL()
{
	HANDLE htest = GetProcessHandleByName("DNF.exe");
	int i = 0;
	int j = 0;
	__asm
	{
		call fun
		mov i, eax
	}

goto end;
	_asm
	{
		mov eax, 0x00400600
		mov ebx,0x100
		add [eax], ebx
		ret
	}
end:
	__asm
	{
		call fun
		mov j, eax
	}
	InjectCreateThreadRunAsm(htest, i + 5, j - 5 - i - 5);
}

void ����CALL(int ����ID)
{
	_asm
	{
		mov ecx, ��������
		push ����ID
		call ����ָ��
	}
}
void �ֽ�Call(int λ������);
void ����Call(int ָ��);
void ˢ��Call(int װ��ָ��);
void ���Call(int ����ID, int ��ɴ���);
void ����Call(int ����ID);
void �ύCall(int ����ID);
void ����Call(int ��ַ);
void ��Ԩ����(int ����ָ��);
void �޵�Call(int ����ָ��);
void ����Call(int ������ַ, int x, int y, int z);
void �������();
void ����Call(int װ������);
void ��ͼCall(int ����);
void ��װCall(int ����ָ��, int װ������);
void ͼֽ��ż(int �������);
void �����˺�(int ָ��, int �˺�);