#pragma once
#include <windows.h>
#include <stdio.h>

int ConvetBufferToInt(BYTE* buffer)
{
	int* result = (int*)buffer;
	return *result;
}

float ConvetBufferToFloat(BYTE* buffer)
{
	float* result = (float*)buffer;
	return *result;
}

double ConvetBufferToDouble(BYTE* buffer)
{
	double* result = (double*)buffer;
	return *result;
}


int ReadProcessMemoryInt(HANDLE hProcess, LPCVOID lpAddress)
{
	BYTE buffer[4] = { 0,0,0,0 };

   BOOL result=	ReadProcessMemory(hProcess, lpAddress, buffer, 4, NULL);
   if (result == FALSE) 
   {
	   printf("ReadProcessMemory failed");
	   return 0;
   }
   else
   {
	   return ConvetBufferToInt(buffer);
   }
  
}

BOOL WriteProcessMemeoryInt(HANDLE hProcess, LPCVOID lpAddress, int value)
{
	BYTE* buffer = (BYTE*)&value;

	BOOL result = WriteProcessMemory(hProcess, lpAddress, buffer, 4, NULL);
	if (result == FALSE)
	{
		printf("WriteProcessMemory failed");
		return 0;
	}
	return 1;
}

float ReadProcessMemoryFloat(HANDLE hProcess, LPCVOID lpAddress)
{
	BYTE buffer[4] = { 0,0,0,0 };

	BOOL result = ReadProcessMemory(hProcess, lpAddress, buffer, 4, NULL);
	if (result == FALSE)
	{
		printf("ReadProcessMemory failed");
		return (float)0;
	}
	else
	{
		return ConvetBufferToFloat(buffer);
	}

}

BOOL WriteProcessMemeoryFloat(HANDLE hProcess, LPCVOID lpAddress, float value)
{
	BYTE* buffer= (BYTE*)&value;

	BOOL result = WriteProcessMemory(hProcess, lpAddress, buffer, 4, NULL);
	if (result == FALSE)
	{
		printf("WriteProcessMemory failed");
		return 0;
	}
	return 1;
}


double ReadProcessMemoryDouble(HANDLE hProcess, LPCVOID lpAddress)
{
	BYTE buffer[8] = { 0,0,0,0,0,0,0,0};

	BOOL result = ReadProcessMemory(hProcess, lpAddress, buffer, 8, NULL);
	if (result == FALSE)
	{
		printf("ReadProcessMemory failed");
		return (double)0;
	}
	else
	{
		return ConvetBufferToDouble(buffer);
	}

}

BOOL WriteProcessMemeoryDouble(HANDLE hProcess, LPCVOID lpAddress, double value)
{
	BYTE* buffer = (BYTE*)&value;
	
	BOOL result = WriteProcessMemory(hProcess, lpAddress, buffer, 8, NULL);
	if (result == FALSE)
	{
		printf("WriteProcessMemory failed");
		return 0;
	}
	return 1;
}

/// Support 100 bytes
byte* ReadProcessMemoryBytes(HANDLE hProcess, LPCVOID lpAddress,size_t length) 
{
	BYTE buffer[100] = { 0 };
	BOOL result = ReadProcessMemory(hProcess, lpAddress, buffer, length, NULL);
	if (result == FALSE)
	{
		printf("ReadProcessMemory failed");
		return NULL;
	}
	return buffer;
}

BOOL WriteProcessMemoryBytes(HANDLE hProcess, LPCVOID lpAddress,size_t length,byte* buffer) 
{
	
	BOOL result = WriteProcessMemory(hProcess, lpAddress, buffer, length, NULL);
	if (result == FALSE)
	{
		printf("WriteProcessMemory failed");
		return 0;
	}
	return 1;
}