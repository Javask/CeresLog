#pragma once
#include <string>

class Loggable {
  friend class LogSystem;

 protected:
  explicit Loggable(std::string name);
  void changeName(std::string newName);

 public:
  virtual ~Loggable() = default;
  void debug(const std::string& message) const;
  void info(const std::string& message) const;
  void warn(const std::string& message) const;
  void error(const std::string& message) const;
  void fatal(const std::string& message) const;

 private:

  static std::string IntToHex(uintptr_t in);

  std::string name;
  std::string id;
};