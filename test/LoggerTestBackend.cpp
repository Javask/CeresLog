#include "LoggerTestBackend.h"
#include "../src/LogSingleton.h"
#include <catch2/catch.hpp>
#include <regex>

LoggerTestBackend::LoggerTestBackend()
    : buffer(std::make_unique<std::string>()) {}

void LoggerTestBackend::write(const std::string& message) {
  *buffer += message;
}

void LoggerTestBackend::flush() { return; }

std::unique_ptr<std::string> LoggerTestBackend::getLog() {
  auto oldBuffer = std::move(buffer);
  buffer = std::make_unique<std::string>();
  return std::move(oldBuffer);
}

TEST_CASE("TestLogger logs correctly", "[logging][testlogger]") {
  auto backend = LoggerTestBackend::getTestBackend();
  LogSingleton::setCustomBackend(backend);

  auto emptyLog = backend->getLog();
  REQUIRE(emptyLog != nullptr);
  REQUIRE(emptyLog->empty());
  LogSingleton::write("Test");
  auto testLog = backend->getLog();
  REQUIRE(testLog != nullptr);
  REQUIRE(*testLog == "Test");
}

TEST_CASE("TestLogger formats correctly", "[logging][testlogger]") {
  auto backend = LoggerTestBackend::getTestBackend();
  LogSingleton::setCustomBackend(backend);
  LogSingleton::log("testMessage");
  auto fileRegex = std::regex(
      R"(\[(\d)?\d:(\d)?\d:(\d)?\d\s(\d)?\d\.(\d)?\d\.\d\d\d\d\]testMessage)");
  auto log = backend->getLog();
  REQUIRE(log != nullptr);
  REQUIRE(std::regex_match(*log, fileRegex));
}

std::shared_ptr<LoggerTestBackend> LoggerTestBackend::getTestBackend() {
  return std::make_shared<LoggerTestBackend>();
}
