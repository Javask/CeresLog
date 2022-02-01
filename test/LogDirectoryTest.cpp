#include "../src/LogDirectory.h"
#include <catch2/catch.hpp>
#include "TemporaryDirectory.h"

TEST_CASE("Log Directory can be found", "[logging][directory]") {
  auto logDir = LogDirectory::getSystemLogDir();
  REQUIRE(logDir.filename() == "log");
  REQUIRE(exists(logDir));
  REQUIRE(is_directory(logDir));
}
