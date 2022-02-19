#include "LogSingleton.h"

#include <utility>
#include "Discovery.h"

void LogSingleton::flush_() {
  std::unique_lock<std::mutex> Lock(backend_mutex);
  if (customBackend_) customBackend_->flush();
  if (logToFile && fileBackend_) fileBackend_->flush();
  if (logToConsole && consoleBackend_) consoleBackend_->flush();
}

void LogSingleton::flush() { LogSingleton::Get()->flush_(); }

void LogSingleton::log(const std::string& message) {
  LogSingleton::Get()->log_(message);
}

void LogSingleton::write(const std::string& message) {
  LogSingleton::Get()->write_(message);
}

void LogSingleton::setCustomBackend(std::shared_ptr<ILoggerBackend> backend_) {
  auto inst = LogSingleton::Get();
  auto Lock = std::unique_lock<std::mutex>(inst->backend_mutex);
  inst->customBackend_ = std::move(backend_);
}

void LogSingleton::setLogToConsole(bool logToConsole) {
  auto inst = LogSingleton::Get();
  inst->logToConsole = logToConsole;
  auto Lock = std::unique_lock<std::mutex>(inst->backend_mutex);
  if (logToConsole && !inst->consoleBackend_) {
    inst->consoleBackend_ = std::make_unique<LoggerConsoleBackend>();
  }
}

void LogSingleton::deactivateLogToDir(bool reset) {
  auto inst = LogSingleton::Get();
  inst->logToFile = false;
  if (reset) {
    auto Lock = std::unique_lock<std::mutex>(inst->backend_mutex);
    inst->fileBackend_ = nullptr;
  }
}

void LogSingleton::activateLogToDir() {
  auto inst = LogSingleton::Get();
  auto Lock = std::unique_lock<std::mutex>(inst->backend_mutex);
  inst->logToFile = true;
  if (!inst->dir) {
    auto systemLogDir = LogDirectory::getSystemLogDir();
    inst->dir = std::make_unique<LogDirectory>(systemLogDir,
                                               std::string(inst->defaultExtension), inst->defaultLimit);
    inst->fileBackend_ = nullptr;
  }
  if (!inst->fileBackend_) {
    inst->fileBackend_ =
        std::make_unique<LoggerFileBackend>(inst->dir->createLogFile());
  }
}

void LogSingleton::activateLogToDir(const std::filesystem::path& path,
                                    int logFileLimit,
                                    const std::string& fileExtension) {
  auto inst = LogSingleton::Get();
  auto Lock = std::unique_lock<std::mutex>(inst->backend_mutex);
  inst->logToFile = true;
  auto outPath = path;
  if (path.is_relative()) {
    outPath = Discovery::getExecutablePath().parent_path();
    outPath /= path;
  }
  inst->dir = std::make_unique<LogDirectory>(outPath, fileExtension, logFileLimit);
  inst->fileBackend_ =
      std::make_unique<LoggerFileBackend>(inst->dir->createLogFile());
}


void LogSingleton::log_(const std::string& message) {
  time_t Time = time(nullptr);
  struct tm Now = {};
#ifndef CERESLOG_PLATFORM_WINDOWS
  localtime_r(&Time, &Now);
#else
  localtime_s(&Now, &Time);
#endif

  std::string Out = "[";
  Out += std::to_string(Now.tm_hour) + ":";
  Out += std::to_string(Now.tm_min) + ":";
  Out += std::to_string(Now.tm_sec) + " ";
  Out += std::to_string(Now.tm_mday) + ".";
  Out += std::to_string(Now.tm_mon + 1) + ".";
  Out += std::to_string(Now.tm_year + 1900) + "]" + message;
  write_(Out);
}

void LogSingleton::write_(const std::string& message) {
  std::unique_lock<std::mutex> Lock(backend_mutex);
  if (customBackend_) customBackend_->write(message);
  if (logToFile && fileBackend_) fileBackend_->write(message);
  if (logToConsole && consoleBackend_) consoleBackend_->write(message);
}
