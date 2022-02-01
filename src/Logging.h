#pragma once
#include <string>

class Logging {
 private:
  Logging() = default;
  ~Logging() = default;

 public:
  static void fatal(const std::string& message);
  static void log(const std::string& message);
};

#define Fatal(A) Logging::fatal("[Fatal]" + A); 

#define Error(A) Logging::log("[Error]" + A);

#define Warn(A) Logging::log("[Warn]" + A);

#define Info(A) Logging::log("[Info]" + A);

#ifdef DEBUG
#define Debug(A) Logging::log("[Debug]["+__FILE__+":"+__LINE__+"]" + A);
#else
#define Debug(A) ;
#endif