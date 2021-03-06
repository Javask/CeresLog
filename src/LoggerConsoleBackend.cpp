#include "LoggerConsoleBackend.h"
#include <iostream>

void LoggerConsoleBackend::write(const std::string& message) {
  std::unique_lock<std::mutex> Lock(lock_);
  std::cout << message;
}

void LoggerConsoleBackend::flush() { std::cout.flush(); }
