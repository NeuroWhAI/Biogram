#include "cFileWriter.h"

using namespace std;



























cFileWriter::cFileWriter()
{

}


cFileWriter::cFileWriter(const char FileName[])
{
	this->Open(FileName);
}


cFileWriter::~cFileWriter()
{
	this->Close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFileWriter::Open(const char FileName[])
{
	m_Stream.open(FileName, ios::binary);

	if(m_Stream.is_open() == false)
	{
		return -1;
	}


	return 0;
}


int cFileWriter::Close()
{
	if(m_Stream.is_open())
	{
		m_Stream.close();
		m_Stream.clear();
	}


	return 0;
}

