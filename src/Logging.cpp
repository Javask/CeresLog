#include <utility>

#include "../include/CeresLog/Logging.h"
#include "LogSingleton.h"

void Logging::fatal(const std::string& message) {
  LogSingleton::log("[Fatal]" + message);
  exit(1);
}

void Logging::log(const std::string& message) { LogSingleton::log(message); }

void Logging::setCustomBackend(std::shared_ptr<ILoggerBackend> newBackend) {
  LogSingleton::setCustomBackend(std::move(newBackend));
}

void Logging::setLogToConsole(bool val) { LogSingleton::setLogToConsole(val); }

void Logging::activateLogToDir() { LogSingleton::activateLogToDir(); }

void Logging::activateLogToDir(const std::filesystem::path& path,
                               int logFileLimit,
                               const std::string& fileExtension) {
  LogSingleton::activateLogToDir(path, logFileLimit, fileExtension);
}

void Logging::deactivateLogToDir(bool reset) {
  LogSingleton::deactivateLogToDir(reset);
}

void Logging::flush() { LogSingleton::flush(); }
