#include "../src/LogDirectory.h"
#include <catch2/catch.hpp>
#include "TemporaryDirectory.h"

TEST_CASE("System Log Directory can be found", "[logging][directory]") {
  auto logDir = LogDirectory::getSystemLogDir();
  REQUIRE(logDir.filename() == "log");
  REQUIRE(exists(logDir));
  REQUIRE(is_directory(logDir));
}

TEST_CASE("Log Directory creates log files", "[logging][directory]") {
  TemporaryDirectory tempDir = TemporaryDirectory();
  auto logDir = LogDirectory::create(tempDir.getPath());
  REQUIRE(logDir != nullptr);
  auto logFile = logDir->createLogFile();
  REQUIRE(exists(logFile));
  REQUIRE(std::filesystem::is_regular_file(logFile));
  REQUIRE(logFile.extension() == ".log");
}


