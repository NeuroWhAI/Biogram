#pragma once
#include <fstream>
#include <Windows.h>























class cFileWriter
{
public:
	cFileWriter();
	cFileWriter(const char FileName[]);

	~cFileWriter();


private:
	std::ofstream m_Stream;


public:
	int Open(const char FileName[]);
	int Close();


public:
	template<typename T>
	int Write(T Val);

	template<>
	int Write<const char*> (const char* String)
	{
		int StrLen = strlen(String);

		m_Stream.write((const char*)&StrLen, sizeof(int));


		m_Stream.write(String, StrLen);


		return 0;
	}

	template<>
	int Write<char*> (char* String)
	{
		int StrLen = strlen(String) + 1;

		m_Stream.write((const char*)&StrLen, sizeof(int));


		m_Stream.write(String, StrLen);


		return 0;
	}

	template<>
	int Write<const wchar_t*> (const wchar_t* String)
	{
		int StrLen = 0;

		while(String[StrLen++] != '\0'); // 카운터에 '\0'포함됨
		StrLen *= 2;

		m_Stream.write((const char*)&StrLen, sizeof(int));


		m_Stream.write((const char*)String, StrLen);
	}

	template<>
	int Write< wchar_t*> (wchar_t* String)
	{
		int StrLen = 0;

		while(String[StrLen++] != '\0'); // 카운터에 '\0'포함됨
		StrLen *= 2;

		m_Stream.write((const char*)&StrLen, sizeof(int));


		m_Stream.write((const char*)String, StrLen);
	}
};

/*-----------------------------------------------------------------------------------------*/

template<typename T>
int cFileWriter::Write(T Val)
{
	m_Stream.write((const char*)&Val, sizeof(T));


	return 0;
}

