#pragma once
#pragma warning(disable:4996)
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

enum LogType
{
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

struct LogEntry
{
	LogType Type;
	std::string Message;
};

class Logger
{
private:
	static std::vector<LogEntry> _messages;

public:
	static void Log(const std::string& message);
	static void Error(const std::string& message);
	static void AddMessage(LogEntry entry);

private:
	static std::string CurrentDateTimeToString();
};
#endif