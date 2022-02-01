#pragma once
#include <mutex>
#include <memory>
#include <functional>

#include "Logger.h"
#include <mutex>
#include <shared_mutex>

class LoggerFactory {
 public:
  static std::unique_ptr<Logger> createLogger();
  static void setBackend(std::shared_ptr<ILoggerBackend> backend);

 private:
  static std::shared_ptr<ILoggerBackend> createDefaultBackend();
  static std::shared_ptr<ILoggerBackend> backend_;
  static std::shared_mutex lock_;
};
