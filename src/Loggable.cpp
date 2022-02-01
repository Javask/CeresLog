#include "../include/CeresLog/Loggable.h"
#include "LoggerFactory.h"


#include <string>
#include <algorithm>
#include <sstream>

std::string Loggable::IntToHex(uintptr_t in) {
  std::stringstream stream;
  stream << std::hex << in;
  return stream.str();
}


Loggable::Loggable(std::string Name)
    : name(Name), id(IntToHex((uintptr_t)this)) {}
void Loggable::changeName(std::string NewName) { name = NewName; }
void Loggable::debugUnformatted(std::string Message) const {
#ifdef CERESLOG_DEBUG
  if (auto Logger = LoggerFactory::createLogger()) Logger->write(Message);
#endif
}
void Loggable::debug(std::string Message) const {
#ifdef CERESLOG_DEBUG
  if (auto Logger = LoggerFactory::createLogger())
    Logger->log("[DEBUG][" + id + "][" + name + "] " + Message + "\n");
#endif
}
void Loggable::info(std::string Message) const {
  if (auto Logger = LoggerFactory::createLogger())
    Logger->log("[INFO][" + id + "][" + name + "] " + Message + "\n");
}
void Loggable::warn(std::string Message) const {
  if (auto Logger = LoggerFactory::createLogger())
    Logger->log("[WARN][" + id + "][" + name + "] " + Message + "\n");
}
void Loggable::error(std::string Message) const {
  if (auto Logger = LoggerFactory::createLogger())
    Logger->log("[ERROR][" + id + "][" + name + "] " + Message + "\n");
}
void Loggable::fatal(std::string Message) const {
  if (auto Logger = LoggerFactory::createLogger()) {
    Logger->log("[FATAL][" + id + "][" + name + "] " + Message + "\n");
  }
  exit(1);
}
