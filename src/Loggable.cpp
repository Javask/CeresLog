#include "../include/CeresLog/Loggable.h"
#include "LogSingleton.h"

#include <string>
#include <sstream>

namespace CeresLog {

std::string IntToHex(uintptr_t in) {
  std::stringstream stream;
  stream << std::hex << in;
  return stream.str();
}

Loggable::Loggable(std::string Name)
    : name(std::move(Name)), id(IntToHex((uintptr_t)this)) {}

void Loggable::changeName(std::string NewName) { name = std::move(NewName); }

void Loggable::debug(const std::string& Message) const {
  if (isDebugBuild)
    LogSingleton::log("[Debug][" + id + "][" + name + "] " + Message + "\n");
}

void Loggable::info(const std::string& Message) const {
  LogSingleton::log("[Info][" + id + "][" + name + "] " + Message + "\n");
}

void Loggable::warn(const std::string& Message) const {
  LogSingleton::log("[Warn][" + id + "][" + name + "] " + Message + "\n");
}

void Loggable::error(const std::string& Message) const {
  LogSingleton::log("[Error][" + id + "][" + name + "] " + Message + "\n");
}

void Loggable::fatal(const std::string& Message) const {
  LogSingleton::log("[Fatal][" + id + "][" + name + "] " + Message + "\n");
  LogSingleton::callFatalCallback();
}

}  // namespace CeresLog
