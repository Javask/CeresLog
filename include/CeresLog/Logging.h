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

#define Fatal(A) Logging::fatal(std::string("[Fatal]") + A); 

#define Error(A) Logging::log(std::string("[Error]") + A);

#define Warn(A) Logging::log(std::string("[Warn]") + A);

#define Info(A) Logging::log(std::string("[Info]") + A);

#ifdef DEBUG
#define Debug(A)                                          \
  Logging::log(std::string("[Debug][") + __FILE__ + ":" + \
               std::to_string(__LINE__) + "]" + A);
#else
#define Debug(A) ;
#endif