#pragma once
#include "ILoggerBackend.h"

#include <vector>
#include <memory>

class LoggerCombinedBackend : public ILoggerBackend {
 public:
  LoggerCombinedBackend() = default;
  void write(const std::string& message) override;

  void addBackend(std::shared_ptr<ILoggerBackend> backend);
  const std::vector<std::shared_ptr<ILoggerBackend>>& getBackends();

 private:
  std::vector<std::shared_ptr<ILoggerBackend>> backends_;
};
