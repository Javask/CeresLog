#pragma once
#include <filesystem>

//Directory class that counts files in it and enforces a limit on filecount of files with correct extension, deleting oldest files. If Limit is Zero or negative dont enforce
class LogDirectory {
 public:
  LogDirectory(const std::filesystem::path& path,const std::string& extension, int fileLimit);

  LogDirectory(LogDirectory& other) = delete;
  LogDirectory& operator=(LogDirectory& other) = delete;
  LogDirectory& operator=(LogDirectory&& other) = delete;

  //Get Path of new Log file in directory, creates Log_${Time and Date}.log
  const std::filesystem::path createLogFile();

  //Returns the log directory at ${Project Root}/log/
  static auto getSystemLogDir() -> std::filesystem::path;

 private:
  // enforces a limit on filecount of files in path with correct extension,
  // deleting oldest files
  void enforceFileLimit();

  // Path of Log directory
  std::filesystem::path path_;

  // Get Name of new Log file, creates Log_${Time and Date}.log
  std::string getLogFileName();

  //Log files to keep in directory
  int fileLimit;

  //Extension of files to keep and to create
  std::string extension;
};
