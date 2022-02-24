#include "LoggableTest.h"
#include "../src/LogSingleton.h"
#include "LoggerTestBackend.h"
#include <catch2/catch.hpp>
#include <regex>

LoggableTest::LoggableTest(std::string name) : Loggable(std::move(name)) {}
void LoggableTest::doInfoLog(const std::string& log) { info(log);}
void LoggableTest::doDebugLog(const std::string& log) {debug(log);}
void LoggableTest::doWarnLog(const std::string& log) { warn(log);}
void LoggableTest::doErrorLog(const std::string& log) { error(log);}
void LoggableTest::doFatalLog(const std::string& log) { fatal(log);}
void LoggableTest::doChangeName(const std::string& newName) {changeName(newName);}

TEST_CASE("Loggable logs correctly","[logging][loggable]"){
  auto backend = std::make_shared<LoggerTestBackend>();
  auto loggableTest = LoggableTest("testName");
  auto testString = "test1 test2";
  auto dateRegexString =
      std::string(R"(\[(\d{1,2}:){2}\d{1,2}\s(\d{1,2}\.){2}\d+\])");
  auto idRegexString = std::string(R"(\[[a-f\d]{1,16}\])");
  auto messageRegexString = std::string(R"(\[testName\](\s)test1(\s)test2\n)");
  LogSingleton::setCustomBackend(backend);
  SECTION("Info logging works correctly"){
    loggableTest.doInfoLog(testString);
    auto logged = *backend->getLog();
    auto infoRegexString = std::string(R"(\[Info\])");
    auto combinedString = dateRegexString+infoRegexString+idRegexString+messageRegexString;
    auto infoRegex = std::regex(combinedString);
    REQUIRE(std::regex_match(logged,infoRegex));
  }
  SECTION("Warning logging works correctly"){
    loggableTest.doWarnLog(testString);
    auto logged = *backend->getLog();
    auto warnRegexString = std::string(R"(\[Warn\])");
    auto combinedString = dateRegexString+warnRegexString+idRegexString+messageRegexString;
    auto warnRegex = std::regex(combinedString);
    REQUIRE(std::regex_match(logged,warnRegex));
  }
  SECTION("Error logging works correctly"){
    loggableTest.doErrorLog(testString);
    auto logged = *backend->getLog();
    auto errorRegexString = std::string(R"(\[Error\])");
    auto combinedString = dateRegexString+errorRegexString+idRegexString+messageRegexString;
    auto errorRegex = std::regex(combinedString);
    REQUIRE(std::regex_match(logged,errorRegex));
  }
  SECTION("Debug logging works correctly") {
    loggableTest.doDebugLog(testString);
    auto logged = *backend->getLog();
    auto debugRegexString = std::string(R"(\[Debug\])");
    auto combinedString = dateRegexString+debugRegexString+idRegexString+messageRegexString;
    auto debugRegex = std::regex(combinedString);
    REQUIRE(std::regex_match(logged,debugRegex));
  }
  SECTION("Change Name works correctly"){
    loggableTest.doChangeName("testName2");
    loggableTest.doInfoLog("test1 test2");
    auto newMessageRegexString = std::string(R"(\[testName2\](\s)test1(\s)test2\n)");
    auto logged = *backend->getLog();
    auto infoRegexString = std::string(R"(\[Info\])");
    auto combinedString = dateRegexString+infoRegexString+idRegexString+newMessageRegexString;
    auto infoRegex = std::regex(combinedString);
    REQUIRE(std::regex_match(logged,infoRegex));
  }
  SECTION("Fatal logging works correctly") {
    std::atomic_bool called = false;
    auto callback = [&called](){called.store(true);};
    LogSingleton::setFatalCallback(callback);
    loggableTest.doFatalLog(testString);
    REQUIRE(called);

    auto logged = *backend->getLog();
    auto fatalRegexString = std::string(R"(\[Fatal\])");
    auto combinedString = dateRegexString+fatalRegexString+idRegexString+messageRegexString;
    auto fatalRegex = std::regex(combinedString);
    REQUIRE(std::regex_match(logged,fatalRegex));
  }
}