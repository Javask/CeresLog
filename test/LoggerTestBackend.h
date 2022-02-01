#pragma once
#include "../src/ILoggerBackend.h"
#include <memory>

class LoggerTestBackend : public ILoggerBackend {
 public:
  LoggerTestBackend();
  void write(const std::string& message) override;
  std::unique_ptr<std::string> getLog();
  static std::shared_ptr<LoggerTestBackend> getTestBackend();

 private:
  std::unique_ptr<std::string> buffer;
};
