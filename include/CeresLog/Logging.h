#pragma once
#include "ILoggerBackend.h"
#include <string>
#include <filesystem>

/// <summary>
/// Logging Interface class, exposes methods to log and to modify the logging behaviour
/// Will start without any logging enabled
/// </summary>
class Logging {
 private:
  Logging() = default;
  ~Logging() = default;

 public:
  /// <summary>
  /// Logs the message as configured, flushes all buffers, aborts the program
  /// </summary>
  /// <param name="message">Message string to log, Time/Date will be prefixed</param>
  static void fatal(const std::string& message);
  /// <summary>
  /// Logs the message as configured
  /// </summary>
  /// <param name="message">Message string to log, Time/Date will be
  /// prefixed</param>
  static void log(const std::string& message);
  /// <summary>
  /// Sets a custom backend to use for logging, in addition to the file and console backends. Only one can be set at any time
  /// </summary>
  /// <param name="newBackend">New Backend to use additionally</param>
  static void setCustomBackend(std::shared_ptr<ILoggerBackend> newBackend);
  /// <summary>
  /// Sets whether or not the log will be output to stdout
  /// </summary>
  /// <param name="val">if true will log to console</param>
  static void setLogToConsole(bool val);
  /// <summary>
  /// Activates logging to standard directory, if directory was overriden will reactivate existing file log
  /// </summary>
  static void activateLogToDir();
  /// <summary>
  /// Activates logging to directory path, enforces a file limit of logFileLimit files with extension fileExtension. 
  /// Will create a new Log file.
  /// </summary>
  /// <param name="path">path of the directory to log to</param>
  /// <param name="logFileLimit">Number of files with extension fileExtension allowes in directory, if 0 will not enforce</param>
  /// <param name="fileExtension">Extension of file to create/delete</param>
  static void activateLogToDir(const std::filesystem::path& path,
                                int logFileLimit,
                                const std::string& fileExtension);
  /// <summary>
  /// Deactivate Logging to file
  /// </summary>
  /// <param name="reset">If true will release log file and create a new one if reactivated</param>
  static void deactivateLogToDir(bool reset = false);

  /// <summary>
  /// FLush all buffers
  /// </summary>
  static void flush();
};

#define Fatal(A) Logging::fatal(std::string("[Fatal]") + A); 

#define Error(A) Logging::log(std::string("[Error]") + A);

#define Warn(A) Logging::log(std::string("[Warn]") + A);

#define Info(A) Logging::log(std::string("[Info]") + A);

#ifndef CERESLOG_DEBUG
#define Debug(A)                                          \
  Logging::log(std::string("[Debug][") + __FILE__ + ":" + \
               std::to_string(__LINE__) + "]" + A);
#else
#define Debug(A) ;
#endif