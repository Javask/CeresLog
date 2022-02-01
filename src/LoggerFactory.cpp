#include "LoggerFactory.h"
#include "LoggerFileBackend.h"
#include "LoggerConsoleBackend.h"
#include "LoggerCombinedBackend.h"

std::unique_ptr<Logger> LoggerFactory::createLogger() {
  if (backend_ == nullptr) {
    std::unique_lock<std::shared_mutex> Lock(lock_);
    if (backend_ == nullptr) {
      backend_ = createDefaultBackend();
    }
  }

  std::shared_lock<std::shared_mutex> Lock(lock_);
  return std::unique_ptr<Logger>(new Logger(backend_));
}

void LoggerFactory::setBackend(std::shared_ptr<ILoggerBackend> backend) {
  std::unique_lock<std::shared_mutex> Lock(lock_);
  backend_ = backend;
}

std::shared_ptr<ILoggerBackend> LoggerFactory::createDefaultBackend() {
  auto CombinedBackend = std::make_shared<LoggerCombinedBackend>();

  auto FileLogger = std::make_shared<LoggerFileBackend>();
  CombinedBackend->addBackend(FileLogger);

  auto ConsoleLogger = std::make_shared<LoggerConsoleBackend>();
  CombinedBackend->addBackend(ConsoleLogger);

  return CombinedBackend;
}

std::shared_ptr<ILoggerBackend> LoggerFactory::backend_ = nullptr;

std::shared_mutex LoggerFactory::lock_ = std::shared_mutex();
