#pragma once
#include <string>

class Loggable {
  friend class LogSystem;

 protected:
  Loggable(std::string name);
  void changeName(std::string newName);

 public:
  virtual ~Loggable() = default;
  void debugUnformatted(std::string message) const;
  void debug(std::string message) const;
  void info(std::string message) const;
  void warn(std::string message) const;
  void error(std::string message) const;
  void fatal(std::string message) const;

 private:

  std::string IntToHex(uintptr_t in);

  std::string name;
  std::string id;
};