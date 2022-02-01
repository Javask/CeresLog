#include "LoggableTest.h"
#include <catch2/catch.hpp>
#include "../src/LoggerFactory.h"
#include "LoggerTestBackend.h"
#include <memory>

LoggableTest::LoggableTest() : Loggable("LoggableTest") {}

#ifdef CERESLOG_DEBUG
TEST_CASE_METHOD(LoggableTest, "Loggable logs correctly",
                 "[logging][loggable]") {
  auto backend = LoggerTestBackend::getTestBackend();
  LoggerFactory::setBackend(backend);
  auto logger = LoggerFactory::createLogger();
  REQUIRE(logger != nullptr);
  debugUnformatted("Test");
  auto log = backend->getLog();
  REQUIRE(log != nullptr);
  REQUIRE(*log == "Test");
}
#endif  //  DEBUG
