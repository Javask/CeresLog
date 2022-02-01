#include "LoggerFileBackend.h"
#include <cassert>
#include <iostream>
#include "LogDirectory.h"

namespace fs = std::filesystem;

LoggerFileBackend::LoggerFileBackend()
    : LoggerFileBackend(LogDirectory::create()->createLogFile()) {}

LoggerFileBackend::LoggerFileBackend(const std::filesystem::path& file) {
  file_ = std::ofstream(file,std::ios::ate|std::ios::out);
  if (!file_.is_open()) {
    std::cout << "Failed to open Logfile!";
  }
}

void LoggerFileBackend::write(const std::string& message) {
  std::unique_lock<std::mutex> Lock(lock_);
  if (file_.is_open()) file_.write(message.c_str(),message.size());
}

LoggerFileBackend::~LoggerFileBackend() { file_.close(); }