#include "LoggerCombinedBackend.h"

void LoggerCombinedBackend::write(const std::string& message) {
  for (auto backend : backends_) {
    backend->write(message);
  }
}

void LoggerCombinedBackend::addBackend(
    std::shared_ptr<ILoggerBackend> backend) {
  backends_.push_back(backend);
}

const std::vector<std::shared_ptr<ILoggerBackend>>&
LoggerCombinedBackend::getBackends() {
  return backends_;
}
