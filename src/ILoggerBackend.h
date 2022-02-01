#pragma once
#include <string>

class ILoggerBackend {
 public:
  ILoggerBackend() = default;
  virtual ~ILoggerBackend() = default;
  virtual void write(const std::string& message) = 0;
};
