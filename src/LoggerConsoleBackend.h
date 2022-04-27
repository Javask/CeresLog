#pragma once
#include "../include/CeresLog/ILoggerBackend.h"
#include <mutex>

namespace CeresLog {

// Logger Backend logging to console
class LoggerConsoleBackend : public ILoggerBackend {
 public:
  LoggerConsoleBackend() = default;
  void write(const std::string& message) override;
  void flush() override;

 private:
  std::mutex lock_;
};

}  // namespace CeresLog