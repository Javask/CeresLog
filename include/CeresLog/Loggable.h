#pragma once
#include <string>

/// <summary>
/// Class that can be inherited from to provide automatical named logging in an object with a unique identifier per object
/// </summary>
class Loggable {
 protected:
  /// <summary>
  /// Initialize the Loggable with the Name to be logged
  /// </summary>
  /// <param name="name">The name that will appear in the log files</param>
  explicit Loggable(std::string name);
  /// <summary>
  /// Change the name that appears in the log files
  /// </summary>
  /// <param name="newName">the new name</param>
  void changeName(std::string newName);

 public:
  virtual ~Loggable() = default;
  /// <summary>
  /// Log a message with the name and id prepended, only if this is a debug build
  /// </summary>
  /// <param name="message">the message to log</param>
  void debug(const std::string& message) const;

  /// <summary>
  /// Log a message with the name and id prepended with log level info
  /// build
  /// </summary>
  /// <param name="message">the message to log</param>
  void info(const std::string& message) const;
  /// <summary>
  /// Log a message with the name and id prepended with log level warn
  /// build
  /// </summary>
  /// <param name="message">the message to log</param>
  void warn(const std::string& message) const;
  /// <summary>
  /// Log a message with the name and id prepended with log level error
  /// build
  /// </summary>
  /// <param name="message">the message to log</param>
  void error(const std::string& message) const;
  /// <summary>
  /// Log a message with the name and id prepended with log level fatal, calling the fatal callback, if set
  /// build
  /// </summary>
  /// <param name="message">the message to log</param>
  void fatal(const std::string& message) const;

 private:
#ifdef NDEBUG
  static const bool isDebugBuild = false;
#else
  static const bool isDebugBuild = true;
#endif

  std::string name;
  std::string id;
};