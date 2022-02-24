#pragma once
#include "../include/CeresLog/Loggable.h"
class LoggableTest : public Loggable{
 public:
  explicit LoggableTest(std::string name);
  ~LoggableTest() override = default;
  void doDebugLog(const std::string&  log);
  void doInfoLog(const std::string& log);
  void doWarnLog(const std::string&  log);
  void doErrorLog(const std::string&  log);
  void doFatalLog(const std::string&  log);
  void doChangeName(const std::string& newName);
};