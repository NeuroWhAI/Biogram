#include "Array.h"
























void Array::Copy(const BYTE* SourceArr, int StartIdxOfSrc, BYTE* DestinationArr, int StartIdxOfDest, int Length)
{
	for(int i=0; i<Length; i++)
	{
		DestinationArr[StartIdxOfDest + i] = SourceArr[StartIdxOfSrc + i];
	}
}


void Array::Resize(BYTE** pArr, int OldSize, int NewSize)
{
	BYTE* NewArr = new BYTE[NewSize];

	int Size = min(OldSize, NewSize);

	for(int i=0; i<Size; i++)
	{
		NewArr[i] = (*pArr)[i];
	}

	if(*pArr != NULL)
		delete[] *pArr;


	*pArr = NewArr;
}

