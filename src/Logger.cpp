#include "Logger.h"

Logger::Logger(std::shared_ptr<ILoggerBackend> backend) : backend_(backend) {}

void Logger::log(const std::string& message) {
  time_t Time = time(nullptr);
  struct tm Now = {};
#ifndef CERESLOG_PLATFORM_WINDOWS
  localtime_r(&Time, &Now);
#else
  localtime_s(&Now, &Time);
#endif

  std::string Out = "[";
  Out += std::to_string(Now.tm_hour) + ":";
  Out += std::to_string(Now.tm_min) + ":";
  Out += std::to_string(Now.tm_sec) + " ";
  Out += std::to_string(Now.tm_mday) + ".";
  Out += std::to_string(Now.tm_mon + 1) + ".";
  Out += std::to_string(Now.tm_year + 1900) + "]" + message;
  backend_->write(Out);
}

void Logger::write(const std::string& message) { backend_->write(message); }
