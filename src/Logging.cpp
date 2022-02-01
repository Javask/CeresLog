#include "Logging.h"
#include "LoggerFactory.h"
#include "LoggerCombinedBackend.h"
#include "LoggerConsoleBackend.h"
#include "LoggerFileBackend.h"

void Logging::fatal(const std::string& message) {
  LoggerFactory::createLogger()->log("[Fatal]" + message);
  exit(1);
}

void Logging::log(const std::string& message) {
  LoggerFactory::createLogger()->log(message);
}
