#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/LoggerFactory.h"
#include "LoggerTestBackend.h"
#include "../include/CeresLog/Logging.h"
#include <regex>
TEST_CASE("Test logging defines", "[logging]") {
  auto backend = LoggerTestBackend::getTestBackend();
  LoggerFactory::setBackend(backend);
  Error("Test");
  auto log = backend->getLog();
  auto fileRegex = std::regex(
      R"(\[(\d)?\d:(\d)?\d:(\d)?\d\s(\d)?\d\.(\d)?\d\.\d\d\d\d\]\[Error\]Test)");
  REQUIRE(log);
  REQUIRE(std::regex_match(*log, fileRegex));
}