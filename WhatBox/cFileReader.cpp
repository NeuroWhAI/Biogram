#include "cFileReader.h"

using namespace std;



























cFileReader::cFileReader()
{

}


cFileReader::cFileReader(const char FileName[])
{
	this->Open(FileName);
}


cFileReader::~cFileReader()
{
	this->Close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFileReader::Open(const char FileName[])
{
	m_Stream.open(FileName, ios::binary);

	if(m_Stream.is_open() == false)
	{
		return -1;
	}


	return 0;
}


int cFileReader::Close()
{
	if(m_Stream.is_open())
	{
		m_Stream.close();
		m_Stream.clear();
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFileReader::ReadString(char pOut[])
{
	int StrLen = 0;

	m_Stream.read((char*)&StrLen, sizeof(int));


	m_Stream.read(pOut, StrLen);


	return StrLen;
}


int cFileReader::ReadString(wchar_t pOut[])
{
	int StrLen = 0;

	m_Stream.read((char*)&StrLen, sizeof(int));


	m_Stream.read((char*)pOut, StrLen);


	return StrLen;
}

