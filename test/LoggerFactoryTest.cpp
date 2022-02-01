#include <catch2/catch.hpp>
#include "../src/LoggerFactory.h"
#include "LoggerTestBackend.h"

TEST_CASE("Logger Factory sets logger correctly", "[logging][loggerfactory]") {
  auto testloggerbackend = LoggerTestBackend::getTestBackend();
  LoggerFactory::setBackend(testloggerbackend);
  LoggerFactory::createLogger()->write("test");
  auto log = testloggerbackend->getLog();
  REQUIRE(log != nullptr);
  REQUIRE(*log == "test");
}
