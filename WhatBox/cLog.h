#pragma once
#include <string>
#include <vector>



















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �α׻�����
// Desc : �α׸� �������
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cLog
{
public:
	cLog();
	~cLog();


private:
	bool m_isShow;
	std::vector<std::string> m_Log;


public:
	int ShowLog();

	int AddLog(const char* FormatLog, ...);
	int AddLog2(const char* FormatLog, va_list vlist);

	bool Toggle();
};

