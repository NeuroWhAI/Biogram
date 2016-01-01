#include "cLog.h"

#include "cCore.h"

#define NUM_LOG 24
#define SIZE_LOG 20



















cLog::cLog()
	: m_isShow(false)
{

}


cLog::~cLog()
{

}

/*-----------------------------------------------------------------------------------------------------*/

int cLog::ShowLog()
{
	if(m_isShow)
	{
		if(m_Log.size() == 0) return 0;


		for(UINT i=m_Log.size()-1; i>=0; i--)
		{
			cCore::Resource.Font0.ShowText(m_Log[i], 16, 512 - (NUM_LOG-i)*SIZE_LOG, 0xffffffff);

			if(i == 0)
				break;
		}
	}


	return 0;
}



int cLog::AddLog(const char* FormatLog, ...)
{
	char Buf[1024] = {0,};


	va_list vlist;
	va_start(vlist, FormatLog); //인자의 시작 주소 설정


	vsprintf_s(Buf, 1024, FormatLog, vlist);


	int idx = m_Log.size();
	m_Log.push_back(std::string());

	for(int i=0; Buf[i] != '\0'; i++)
	{
		m_Log[idx].push_back(Buf[i]);
	}
	m_Log[idx].push_back('\0');


	if(m_Log.size() > NUM_LOG)
	{// 일정갯수 이상 많아지면 가장 마지막것을 지움
		m_Log.erase(m_Log.begin());
	}


	va_end(vlist);
	return 0;
}


int cLog::AddLog2(const char* FormatLog, va_list vlist)
{
	char Buf[1024] = {0,};
	vsprintf_s(Buf, 1024, FormatLog, vlist);


	int idx = m_Log.size();
	m_Log.push_back(std::string());

	for(int i=0; Buf[i] != '\0'; i++)
	{
		m_Log[idx].push_back(Buf[i]);
	}
	m_Log[idx].push_back('\0');


	if(m_Log.size() > NUM_LOG)
	{// 일정갯수 이상 많아지면 가장 마지막것을 지움
		m_Log.erase(m_Log.begin());
	}


	return 0;
}



bool cLog::Toggle()
{
	return (m_isShow = !m_isShow);
}

