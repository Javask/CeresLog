#include "Discovery.h"
#include <Utilities/FileUtils.h>
#include <vector>
#include <iostream>

namespace CeresLog {

bool Discovery::isSet = false;

std::filesystem::path Discovery::executablePath = std::filesystem::path();

void Discovery::overrideExecutablePath(const std::filesystem::path& path) {
  executablePath = path;
  isSet = true;
}

void Discovery::resetExecutablePath() { isSet = false; }

std::filesystem::path Discovery::getExecutablePath() {
  if (isSet) return executablePath;
  return Utilities::getExecutablePath();
}

}  // namespace CeresLog