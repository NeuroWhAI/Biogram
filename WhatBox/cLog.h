#pragma once
#include <string>
#include <vector>



















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 로그생성기
// Desc : 로그를 출력해줌
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

