#include "Logger.h"



























Logger::Logger()
{
	
}


Logger::~Logger()
{

}

//#################################################################

int Logger::log()
{
	whenLog(m_buffer.str());

	m_buffer.str("");
	m_buffer.clear();


	return 0;
}

