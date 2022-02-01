#include "../src/LoggerFileBackend.h"
#include "../src/Logger.h"
#include "TemporaryDirectory.h"
#include "LoggerTestBackend.h"
#include <catch2/catch.hpp>
#include <regex>
#include <memory>
#include <istream>
#include <fstream>

namespace fs = std::filesystem;

TEST_CASE("Logger writes to file", "[logging][logger]") {
  auto tmpDir = TemporaryDirectory();
  auto tmpFile = tmpDir.createTempFile();
  {
    auto backend = std::shared_ptr<LoggerFileBackend>(
        new LoggerFileBackend(tmpFile));
    auto logger = Logger(backend);
    logger.write("testMessage");
  }
  auto stream = std::ifstream(tmpFile, std::ios::in | std::ios::ate);
  size_t ate = stream.tellg();
  stream.seekg(std::ios::beg);
  size_t fileSize = ate - stream.tellg();
  auto content = std::vector<char>(fileSize + 1);
  stream.read(content.data(), fileSize);
  REQUIRE(std::string(content.data()) == "testMessage");
}

TEST_CASE("Logger formats correctly", "[logging][logger]") {
  auto backend = LoggerTestBackend::getTestBackend();
  {
    auto logger = Logger(backend);
    logger.log("testMessage");
  }
  auto log = backend->getLog();
  REQUIRE(log != nullptr);
  auto fileRegex = std::regex(
      R"(\[(\d)?\d:(\d)?\d:(\d)?\d\s(\d)?\d\.(\d)?\d\.\d\d\d\d\]testMessage)");
  REQUIRE(std::regex_match(*log, fileRegex));
}
