#pragma once
#include <string>

class Logger
{
public:
  static void info( const std::string& logEntry)
  {
    log(logEntry, LogLevel_INFO);
  }

  static void error( const std::string& logEntry)
  {
    log(logEntry, LogLevel_ERROR);
  }

private:
  static void log(const std::string& logEntry, LogLevel logLevel)
  {
    log(logEntry, logLevel, "WertiPlugin", 0);
  }

  static void log(const std::string& logEntry, LogLevel logLevel, uint64 logID)
  {
    log(logEntry, logLevel, "WertiPlugin", logID);
  }

  static void log(const std::string& logEntry, LogLevel logLevel, const std::string& channel)
  {
    log(logEntry, logLevel, channel, 0);
  }

  static void log( const std::string& logEntry, LogLevel logLevel, const std::string& channel, uint64 logID)
  {
    ts3Functions.logMessage(logEntry.c_str(), logLevel, channel.c_str(), logID);
  }
};
