#pragma once
#include <Windows.h>



















class Array
{
public:
	static void Copy(const BYTE* SourceArr, int StartIdxOfSrc, BYTE* DestinationArr, int StartIdxOfDest, int Length);
	static void Resize(BYTE** pArr, int OldSize, int NewSize);
};

