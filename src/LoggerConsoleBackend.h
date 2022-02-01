#pragma once
#include "ILoggerBackend.h"
#include <mutex>

class LoggerConsoleBackend : public ILoggerBackend {
 public:
  LoggerConsoleBackend() = default;
  void write(const std::string& message) override;

 private:
  std::mutex lock_;
};
