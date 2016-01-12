#pragma once

#include <string>
#include <sstream>



























class Logger
{
public:
	Logger();
	virtual ~Logger();


private:
	std::ostringstream m_buffer;


public:
	int log();

	template <typename T>
	int log(const T& arg);

	template <typename T, typename... ARGS>
	int log(const T& arg, ARGS... args);


protected:
	virtual void whenLog(std::string text) = 0;
};


#include "Logger.inl"