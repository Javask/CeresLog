#pragma once
#include "ILoggerBackend.h"
#include <ostream>
#include <fstream>
#include <mutex>

class LoggerFileBackend : public ILoggerBackend {
 public:
  LoggerFileBackend();
  LoggerFileBackend(const std::filesystem::path& file);
  ~LoggerFileBackend();
  LoggerFileBackend(LoggerFileBackend& other) = delete;
  LoggerFileBackend& operator=(LoggerFileBackend& other) = delete;
  void write(const std::string& message) override;

 private:
  std::ofstream file_;
  std::mutex lock_;
};
