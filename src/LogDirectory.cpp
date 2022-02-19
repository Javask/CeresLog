#include "LogDirectory.h"
#include "Discovery.h"

#include <map>
#include <fstream>
#include <iostream>
#include <ostream>

namespace fs = std::filesystem;

LogDirectory::LogDirectory(std::filesystem::path& path,
                           std::string extension, int fileLimit)
    : path_(path), extension(std::move(extension)), fileLimit(fileLimit) {
  if (!fs::exists(path)) {
    if (!fs::create_directories(path)) {
      std::cerr << "Failed to create logging directory "
                << path.generic_string() << std::endl;
      abort();
    }
  } else {
    if (!fs::is_directory(path)) {
      std::cerr << "Logging directory path already exists as non directory: "
                << path.generic_string() << std::endl;
      abort();
    }
  }
  enforceFileLimit();
}

void LogDirectory::enforceFileLimit() {
  if (fileLimit <= 0) return;

  std::map<fs::file_time_type, fs::path> FilenameMap;
  for (auto& LogFile : fs::directory_iterator(path_)) {
    auto LWT = fs::last_write_time(LogFile);
    if (LogFile.path().extension().generic_string() == extension) {
      FilenameMap.insert(std::make_pair(LWT, LogFile.path().generic_string()));
    }
  }
  size_t Counter = 0;
  size_t Max = FilenameMap.size();
  if (Max > fileLimit) {
    size_t ToGo = Max - fileLimit;
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
  auto ExecPath = Discovery::getExecutablePath();
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
  return Filename+extension;
}


std::filesystem::path LogDirectory::createLogFile() {
  auto outPath = fs::path(path_);
  outPath.append(getLogFileName());
  auto temp = std::ofstream(outPath);
  temp.close();
  enforceFileLimit();
  return outPath;
}