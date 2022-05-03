#include "TemporaryDirectory.h"
#include <Utilities/FileUtils.h>
#include <Utilities/StringUtils.h>
#include <string>
#include <catch2/catch.hpp>
#include <fstream>
#include <cstring>
#include <utility>

namespace fs = std::filesystem;

TemporaryDirectory::TemporaryDirectory() : TemporaryDirectory(".tmp") {}

TemporaryDirectory::TemporaryDirectory(std::string fileExtension)
    : extension_(std::move(fileExtension)), path_(Utilities::createTempDir()) {}

TemporaryDirectory::~TemporaryDirectory() { remove_all(path_); }

std::filesystem::path TemporaryDirectory::createTempFile() {
  auto outPath =
      fs::path(path_).append(Utilities::generateRandomString(8) + extension_);
  auto stream = std::ofstream(outPath);
  stream.close();
  return outPath;
}

std::filesystem::path TemporaryDirectory::createNewFileInDir(
    const std::string& name) {
  auto outPath = fs::path(path_).append(name + extension_);
  auto stream = std::ofstream(outPath);
  stream.close();
  return outPath;
}

std::filesystem::path TemporaryDirectory::getPath() const { return path_; }

TEST_CASE("Temporary Directory created", "[utility][temporarydir]") {
  {
    auto tempDir = TemporaryDirectory();
    REQUIRE(fs::exists(tempDir.getPath()));
  }
}

TEST_CASE("Temporary File created", "[utility][temporarydir]") {
  {
    auto tempDir = TemporaryDirectory();
    auto tmpFile = tempDir.createTempFile();
    REQUIRE(fs::exists(tmpFile));
  }
}

TEST_CASE("Named Temporary File created", "[utility][temporarydir]") {
  {
    auto tempDir = TemporaryDirectory();
    auto tmpFile = tempDir.createNewFileInDir("testFile");
    REQUIRE(fs::exists(tmpFile));
    REQUIRE(tmpFile.filename() == "testFile.tmp");
  }
}
