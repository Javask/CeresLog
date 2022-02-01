#include "../src/LoggerFileBackend.h"
#include <catch2/catch.hpp>
#include "TemporaryDirectory.h"

TEST_CASE("Logger File Backend opens file correctly",
          "[logging][loggerfilebackend]") {
  auto tmpDir = TemporaryDirectory();
  auto tmpFile = tmpDir.createTempFile();
  auto tmpPath = tmpFile;
  {
    auto backend = LoggerFileBackend(std::move(tmpFile));
    backend.write("test");
  }
  auto stream = std::ifstream(tmpPath, std::ios::in | std::ios::ate);
  auto streamend = stream.tellg();
  stream.seekg(std::ios::beg);
  auto fileSize = streamend - stream.tellg();
  auto content = std::vector<char>(fileSize + 1);
  stream.read(content.data(), fileSize);
  stream.close();
  REQUIRE(std::string(content.data()) == "test");
}
