# CeresLog 
Simple spin-off of my shitty log code i keep rewriting so i stop doing that.\
Uses the [CPM package manager](https://github.com/cpm-cmake/CPM.cmake) for testing.

## CMake options
To disable automatic build of test executable use CMake option CERESLOG_BUILD_TESTS.

## Configuration
By default CeresLog will not log to anywhere.\
To enable logging to console simply set Logging::setLogToConsole to true.\
To enable file logging, use Logging::activateLogToDir and its overloads.\
If no arguments are provided, will create a folder called "log" in the directory of the executable.\
However a directory path can be provided to change this. \
In the directory a file limit (default: 10) will be enforced. This will only delete files of the configured file extension (default: ".log").\
The limit can be disabled by setting it to 0 and the extension can also be changed in a call to Logging::activateLogToDir.
