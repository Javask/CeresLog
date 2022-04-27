#pragma once
#include "../include/CeresLog/ILoggerBackend.h"
#include <ostream>
#include <fstream>
#include <mutex>
#include <filesystem>

namespace CeresLog {

class LoggerFileBackend : public ILoggerBackend {
 public:
  explicit LoggerFileBackend(const std::filesystem::path& file);
  ~LoggerFileBackend() override;
  LoggerFileBackend(LoggerFileBackend& other) = delete;
  LoggerFileBackend& operator=(LoggerFileBackend& other) = delete;
  void write(const std::string& message) override;
  void flush() override;

 private:
  std::ofstream file_;
  std::mutex lock_;
};

}  // namespace CeresLog
