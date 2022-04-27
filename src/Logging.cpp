#include <utility>

#include "../include/CeresLog/Logging.h"
#include "LogSingleton.h"

namespace CeresLog {

void Logging::fatal(const std::string& message) {
  LogSingleton::log(message);
  LogSingleton::callFatalCallback();
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

void Logging::setFatalCallback(std::function<void()> callback) {
  LogSingleton::setFatalCallback(std::move(callback));
}

void Logging::debug(const std::string& message) {
  if (isDebugBuild) {
    LogSingleton::log(message);
  }
}

}  // namespace CeresLog