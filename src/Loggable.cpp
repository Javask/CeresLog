#include "../include/CeresLog/Loggable.h"
#include "LogSingleton.h"

#include <string>
#include <sstream>

std::string Loggable::IntToHex(uintptr_t in) {
  std::stringstream stream;
  stream << std::hex << in;
  return stream.str();
}

Loggable::Loggable(std::string Name)
    : name(std::move(Name)), id(IntToHex((uintptr_t)this)) {}

void Loggable::changeName(std::string NewName) { name = std::move(NewName); }

void Loggable::debug(const std::string& Message) const {
#ifdef CERESLOG_DEBUG
  LogSingleton::log("[DEBUG][" + id + "][" + name + "] " + Message + "\n");
#endif
}

void Loggable::info(const std::string& Message) const {
  LogSingleton::log("[INFO][" + id + "][" + name + "] " + Message + "\n");
}

void Loggable::warn(const std::string& Message) const {
  LogSingleton::log("[WARN][" + id + "][" + name + "] " + Message + "\n");
}

void Loggable::error(const std::string& Message) const {
  LogSingleton::log("[ERROR][" + id + "][" + name + "] " + Message + "\n");
}

void Loggable::fatal(const std::string& Message) const {
  LogSingleton::log("[FATAL][" + id + "][" + name + "] " + Message + "\n");
  exit(1);
}
