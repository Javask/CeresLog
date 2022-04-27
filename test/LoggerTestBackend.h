#pragma once
#include "../include/CeresLog/ILoggerBackend.h"
#include <memory>

namespace CeresLog {
class LoggerTestBackend : public ILoggerBackend {
 public:
  LoggerTestBackend();
  void write(const std::string& message) override;
  void flush() override;
  std::unique_ptr<std::string> getLog();
  static std::shared_ptr<LoggerTestBackend> getTestBackend();

 private:
  std::unique_ptr<std::string> buffer;
};
}  // namespace CeresLog
