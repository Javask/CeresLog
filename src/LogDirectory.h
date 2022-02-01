#pragma once
#include <filesystem>

class LogDirectory {
 public:
  static std::unique_ptr<LogDirectory> create();

  static std::unique_ptr<LogDirectory> create(
      const std::filesystem::path& path);

  LogDirectory(LogDirectory& other) = delete;
  LogDirectory& operator=(LogDirectory& other) = delete;
  LogDirectory& operator=(LogDirectory&& other) = delete;

  const std::filesystem::path createLogFile();

  static auto getSystemLogDir() -> std::filesystem::path;

 protected:
  LogDirectory();
  LogDirectory(const std::filesystem::path& path);

 private:
  void enforceFileLimit();
  std::filesystem::path path_;
  static std::string getLogFileName();
  static const int MaxLogFileCount = 10;
  static const std::string LogFileExtension;
};
