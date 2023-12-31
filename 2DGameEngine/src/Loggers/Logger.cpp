#include "Logger.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

std::vector<LogEntry> Logger::_messages;

void Logger::Log(const std::string& message)
{
	LogEntry logEntry;
	logEntry.Type = LOG_INFO;
	logEntry.Message = "LOG: [" + CurrentDateTimeToString() + "]: " + message;
	std::cout << "\x1B[32m" << logEntry.Message << "\033[0m" << std::endl;
	AddMessage(logEntry);
}

void Logger::Error(const std::string& message)
{
	LogEntry logEntry;
	logEntry.Type = LOG_ERROR;
	logEntry.Message = "ERROR: [" + CurrentDateTimeToString() + "]: " + message;
	std::cerr << "\x1B[91m" << logEntry.Message << "\033[0m" << std::endl;
	AddMessage(logEntry);
}

void Logger::AddMessage(LogEntry entry) 
{
	_messages.push_back(entry);
}

std::string Logger::CurrentDateTimeToString()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
	return output;
}