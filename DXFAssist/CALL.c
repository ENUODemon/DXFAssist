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

void 主线CALL(int 任务ID)
{
	_asm
	{
		mov ecx, 任务数据
		push 任务ID
		call 任务指针
	}
}
void 分解Call(int 位置索引);
void 卖物Call(int 指针);
void 刷新Call(int 装备指针);
void 完成Call(int 任务ID, int 完成次数);
void 接受Call(int 任务ID);
void 提交Call(int 任务ID);
void 爆物Call(int 地址);
void 深渊出怪(int 对象指针);
void 无敌Call(int 人物指针);
void 坐标Call(int 触发地址, int x, int y, int z);
void 任意材料();
void 创建Call(int 装备代码);
void 过图Call(int 方向);
void 换装Call(int 触发指针, int 装备代码);
void 图纸人偶(int 怪物代码);
void 附加伤害(int 指针, int 伤害);