#include "Logger.h"



























template <typename T>
int Logger::log(const T& arg)
{
	m_buffer << arg;

	whenLog(m_buffer.str());

	m_buffer.str("");
	m_buffer.clear();


	return 0;
}


template <typename T, typename... ARGS>
int Logger::log(const T& arg, ARGS... args)
{
	m_buffer << arg;


	return log(args...);
}

