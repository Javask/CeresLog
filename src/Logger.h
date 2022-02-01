#pragma once
#include "ILoggerBackend.h"
#include <memory>
class Logger {
 public:
  Logger(std::shared_ptr<ILoggerBackend> backend);
  void log(const std::string& message);
  void write(const std::string& message);

 private:
  std::shared_ptr<ILoggerBackend> backend_;
};
