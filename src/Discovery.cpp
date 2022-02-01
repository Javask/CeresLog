#include "Discovery.h"
#ifdef PLATFORM_WINDOWS
#include <Windows.h>

#include <vector>
#else
#include <linux/limits.h>
#include <unistd.h>

#include <vector>
#endif

std::filesystem::path GetExecutablePath() {
#ifdef PLATFORM_WINDOWS
  std::vector<char> FileName = std::vector<char>(128);
  while (GetModuleFileNameA(NULL, FileName.data(), (DWORD)FileName.size()) ==
         (DWORD)FileName.size()) {
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) abort();
    FileName.resize(FileName.size() + 128);
  }
  return std::filesystem::path(FileName.data());
#else
  char FileName[PATH_MAX] = {};
  ssize_t count = readlink("/proc/self/exe", FileName, PATH_MAX);
  return std::string(FileName, (count > 0) ? count : 0);
#endif
}
