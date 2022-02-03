#pragma once
#include <string>
#include <mutex>
#include <atomic>
#include "../include/CeresLog/ILoggerBackend.h"
#include "LoggerConsoleBackend.h"
#include "LoggerFileBackend.h"
#include "LogDirectory.h"
#include "Singleton.h"

class LogSingleton :public Singleton<LogSingleton>{
  friend class Singleton<LogSingleton>;
  friend class Destroyer<LogSingleton>;
 protected:
  LogSingleton() = default;
  ~LogSingleton() = default;

 public:
  static void flush();
  static void log(const std::string& message);
  static void write(const std::string& message);
  static void setCustomBackend(std::shared_ptr<ILoggerBackend> backend_);  
  static void setLogToConsole(bool logToConsole);
  static void deactivateLogToDir(bool reset);
  static void activateLogToDir();
  static void activateLogToDir(const std::filesystem::path& path,
                                int logFileLimit,
                                const std::string& fileExtension);

 private:
  void flush_();
  void log_(const std::string& message);
  void write_(const std::string& message);
  std::mutex backend_mutex;
  bool initialized = false;
  std::unique_ptr <LogDirectory> dir = nullptr;
  std::shared_ptr<ILoggerBackend> customBackend_ = nullptr;
  std::atomic_bool logToFile = false, logToConsole = false;
  std::unique_ptr<LoggerFileBackend> fileBackend_ = nullptr;
  std::unique_ptr<LoggerConsoleBackend> consoleBackend_ = nullptr;

  const int defaultLimit = 10;
  const char* defaultExtension = ".log";
};