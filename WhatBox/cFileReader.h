#pragma once
#include <fstream>
#include <Windows.h>























class cFileReader
{
public:
	cFileReader();
	cFileReader(const char FileName[]);

	~cFileReader();


private:
	std::ifstream m_Stream;


public:
	int Open(const char FileName[]);
	int Close();


public:
	template<typename T>
	T Read();

	int ReadString(char pOut[]);
	int ReadString(wchar_t pOut[]);
};


template<typename T>
T cFileReader::Read()
{
	T temp;
	m_Stream.read((char*)&temp, sizeof(T));


	return temp;
}

