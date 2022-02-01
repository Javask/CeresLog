#include "../src/LogDirectory.h"
#include <catch2/catch.hpp>
#include "TemporaryDirectory.h"
#include <regex>

TEST_CASE("Log File correctly creates file in Directory",
          "[logging][logfile]") {
  auto tmpDir =
      std::unique_ptr<TemporaryDirectory>(new TemporaryDirectory());
  auto logDir = LogDirectory::create(tmpDir->getPath());
  auto logFile = logDir->createLogFile();
  REQUIRE(exists(logFile));
  auto fileRegex = std::regex(
      R"(Log\_\d\d\d\d\_(\d)?\d\_(\d)?\d\_(\d)?\d\_(\d)?\d\_(\d)?\d\.log)");
  REQUIRE(std::regex_match(logFile.filename().generic_string(), fileRegex));
  REQUIRE(std::filesystem::is_regular_file(logFile));
}
