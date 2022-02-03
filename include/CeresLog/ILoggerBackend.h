#pragma once
#include <string>

///<summary>
///Replaceable Logger Backend, represents an output for the Logging System
///</summary>
class ILoggerBackend {
 public:
  ILoggerBackend() = default;
  virtual ~ILoggerBackend() = default;

  /// <summary>
  /// Output string to desired medium without applying any formatting
  /// </summary>
  /// <param name="message">String to be output</param>
  virtual void write(const std::string& message) = 0;

  /// <summary>
  /// Flush buffers
  /// </summary>
  virtual void flush() = 0;
};
