#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "LoggerTestBackend.h"
#include "TemporaryDirectory.h"
#include "../include/CeresLog/Logging.h"
#include <regex>
#include <vector>
#include "../src/Discovery.h"
#include <filesystem>
#include <istream>
#include <fstream>

namespace fs = std::filesystem;

TEST_CASE("Test logging defines", "[logging]") {
  auto backend = LoggerTestBackend::getTestBackend();
  Logging::setCustomBackend(backend);
  Error("Test");
  auto log = backend->getLog();
  auto fileRegex = std::regex(
      R"(\[(\d)?\d:(\d)?\d:(\d)?\d\s(\d)?\d\.(\d)?\d\.\d\d\d\d\]\[Error\]Test)");
  REQUIRE(log);
  REQUIRE(std::regex_match(*log, fileRegex));
}

TEST_CASE("Test logging to file in temporary Directory", "[logging]") {
  auto backend = LoggerTestBackend::getTestBackend();
  auto tempDir = TemporaryDirectory();
  Logging::setCustomBackend(backend);
  Logging::activateLogToDir(tempDir.getPath(), 0, ".tmp");
  std::vector<fs::path> Filenames;
  for (auto& LogFile : fs::directory_iterator(tempDir.getPath())) {
    Filenames.push_back(LogFile.path());
  }
  auto fileNameRegex = std::regex(
      R"(Log_\d\d\d\d_\d?\d_\d?\d_\d?\d_\d?\d_\d?\d\.tmp)");
  REQUIRE(Filenames.size() == 1);
  auto filename = Filenames[0].filename().generic_string();
  REQUIRE(std::regex_match(filename, fileNameRegex));
  Logging::deactivateLogToDir(true);
}


TEST_CASE("Test logging to file in Directory postfix", "[logging][discovery]") {
  auto backend = LoggerTestBackend::getTestBackend();
  auto tempDir = TemporaryDirectory();
  auto tempDir2 = tempDir.getPath();
  tempDir2 /= "test";
  REQUIRE(fs::create_directory(tempDir2));
  Discovery::overrideExecutablePath(tempDir2);
  Logging::setCustomBackend(backend);

  Logging::activateLogToDir(fs::path("test2")/".."/"log", 0, ".tmp");
  auto finalPath = tempDir.getPath();
  finalPath.append("log");

  auto test = tempDir.getPath();
  test = test / "test2"/ ".."/ "log";
  REQUIRE(fs::exists(finalPath));
  std::vector<fs::path> Filenames;
  for (auto& LogFile : fs::directory_iterator(finalPath)) {
    Filenames.push_back(LogFile.path());
  }
  auto fileNameRegex =
      std::regex(R"(Log_\d\d\d\d_\d?\d_\d?\d_\d?\d_\d?\d_\d?\d\.tmp)");
  REQUIRE(Filenames.size() == 1);
  auto filename = Filenames[0].filename().generic_string();
  REQUIRE(std::regex_match(filename, fileNameRegex));
  Logging::deactivateLogToDir(true);
  Discovery::resetExecutablePath();
}

TEST_CASE("Test successful logging to file", "[logging]") {
  auto backend = LoggerTestBackend::getTestBackend();
  auto tempDir = TemporaryDirectory();
  Logging::setCustomBackend(backend);
  Logging::activateLogToDir(tempDir.getPath(), 0, ".tmp");
  std::vector<fs::path> Filenames;
  for (auto& LogFile : fs::directory_iterator(tempDir.getPath())) {
    Filenames.push_back(LogFile.path());
  }
  REQUIRE(Filenames.size() == 1);
  Error("Testlog");
  Logging::flush();
  Logging::deactivateLogToDir(false);
  std::ifstream filestream = std::ifstream(Filenames[0].generic_string(),std::ios::in|std::ios::ate);
  REQUIRE(filestream.is_open());
  auto endPos = filestream.tellg();
  filestream.seekg(std::ios::beg);
  auto size = endPos - filestream.tellg();
  std::vector<char> data = std::vector<char>(size+1);
  filestream.read(data.data(), size);
  filestream.close();
  std::string readData = std::string(data.data());
  std::string testData = *backend->getLog();
  REQUIRE(readData == testData);
  Error("TestLog2");
  Logging::flush();
  Logging::deactivateLogToDir(false);
  filestream = std::ifstream(Filenames[0].generic_string(),
                                           std::ios::in | std::ios::ate);
  REQUIRE(filestream.is_open());
  endPos = filestream.tellg();
  filestream.seekg(std::ios::beg);
  size = endPos - filestream.tellg();
  data = std::vector<char>(size + 1);
  filestream.read(data.data(), size);
  filestream.close();
  readData = std::string(data.data());
  testData += *backend->getLog();
  REQUIRE(readData != testData);
  Logging::deactivateLogToDir(true);
}