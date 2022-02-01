#include "LogDirectory.h"
#include "Discovery.h"

#include <map>
#include <fstream>
#include <ostream>

namespace fs = std::filesystem;

const std::string LogDirectory::LogFileExtension = ".log";

LogDirectory::LogDirectory() : LogDirectory(getSystemLogDir()) {}

LogDirectory::LogDirectory(const std::filesystem::path& path) {
  path_ = path;
  enforceFileLimit();
}

void LogDirectory::enforceFileLimit() {
  std::map<fs::file_time_type, fs::path> FilenameMap;
  for (auto& LogFile : fs::directory_iterator(path_)) {
    auto LWT = fs::last_write_time(LogFile);
    if (LogFile.path().extension().generic_string() == LogFileExtension) {
      FilenameMap.insert(std::make_pair(LWT, LogFile.path().generic_string()));
    }
  }
  size_t Counter = 0;
  size_t Max = FilenameMap.size();
  if (Max > MaxLogFileCount) {
    size_t ToGo = Max - MaxLogFileCount;
    for (const auto& LogFileKey : FilenameMap) {
      if (Counter == ToGo) {
        break;
      }
      fs::remove(LogFileKey.second);
      Counter++;
    }
  }
}

auto LogDirectory::getSystemLogDir() -> std::filesystem::path {
  auto ExecPath = GetExecutablePath();
  auto LogDir = ExecPath.parent_path().parent_path();
  LogDir.append("log");
  if (!fs::is_directory(LogDir)) {
    if (fs::exists(LogDir)) {
      abort();
    }
    if (!fs::create_directories(LogDir)) {
      abort();
    }
    if (!fs::is_directory(LogDir)) {
      abort();
    }
  }
  return LogDir;
}

std::string LogDirectory::getLogFileName() {
  time_t Time = time(nullptr);
  struct tm Now = {};
#ifndef CERESLOG_PLATFORM_WINDOWS
  localtime_r(&Time, &Now);
#else
  localtime_s(&Now, &Time);
#endif

  std::string Filename = "Log_";
  Filename += std::to_string(Now.tm_year + 1900) + "_";
  Filename += std::to_string(Now.tm_mon + 1) + "_";
  Filename += std::to_string(Now.tm_mday) + "_";
  Filename += std::to_string(Now.tm_hour) + "_";
  Filename += std::to_string(Now.tm_min) + "_";
  Filename += std::to_string(Now.tm_sec);
  return Filename+LogFileExtension;
}

std::unique_ptr<LogDirectory> LogDirectory::create() {
  return std::unique_ptr<LogDirectory>(new LogDirectory());
}

std::unique_ptr<LogDirectory> LogDirectory::create(
    const std::filesystem::path& path) {
  return std::unique_ptr<LogDirectory>(new LogDirectory(path));
}

const std::filesystem::path LogDirectory::createLogFile() {
  auto outPath = fs::path(path_);
  outPath.append(getLogFileName());
  auto temp = std::ofstream(outPath);
  temp.close();
  enforceFileLimit();
  return outPath;
}