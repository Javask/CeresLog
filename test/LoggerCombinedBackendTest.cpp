#include "../src/LoggerCombinedBackend.h"
#include <catch2/catch.hpp>
#include "LoggerTestBackend.h"

TEST_CASE("Combined Backend successfully combines backends",
          "[logging][loggercombinedbackend]") {
  auto cbackend = LoggerCombinedBackend();
  auto tbackend1 = LoggerTestBackend::getTestBackend();
  auto tbackend2 = LoggerTestBackend::getTestBackend();
  cbackend.addBackend(tbackend1);
  cbackend.addBackend(tbackend2);
  cbackend.write("test");
  auto log1 = tbackend1->getLog();
  auto log2 = tbackend2->getLog();
  REQUIRE((log1 != nullptr && log2 != nullptr));
  REQUIRE((*log1 == "test" && *log2 == "test"));
}
