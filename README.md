# LinuxLogger

Stream logger for development under linux

## Description

Stream logger, supports output into file and console

## Installation

### Linux

If no git installed, install it:
$ sudo apt install git

Make sure you have cmake installed. If no - install it:
$ sudo apt-get -y install cmake

Create and enter directory for project to install into
$ mkdir Logger
$ cd Logger

Clone project onto your current directory
$ git clone https://github.com/TutyhinAlexander/LinuxLogger.git .

Create a new build directory and change into it:
$ mkdir build
$ cd build

Run cmake on the parent directory to generate makefile:
$ cmake ..

Run make on the generated makefile to generate the static library libLogger.a:
$ make

To install the headers on your system:
$ sudo make install

## Using

1) Before start logging, you should call Logger::Init(loggerParams);
where loggerParams is a struct with logger params:
    loggerParams.fileName - log file prefix (full file name will be in format <fileName>_[datatime].txt and it will be stored in ./Logs folder);
		if NULL - no file will be created
    loggerParams.maxLogFiles - log files limit in ./Logs folder
    loggerParams.useTimestamp - if true - before each message will be added [datatime]
    loggerParams.logToConsole - true if you need log to console

2) Start loging with Logger::Log(msg, ...); 
	msg is printf like format string
	
## Using This Project As A CMake Dependency

Add folowwing to your main CMakeLists.txt:

find_package(Logger REQUIRED)
target_link_libraries(<your_target_project> DebugTools::Logger)


## Examples

#include "Logger/Logger.h"

using namespace DebugTools;

int main()
{
    LoggerParams loggerParams;
    loggerParams.fileName = "Log";
    loggerParams.maxLogFiles = 10;
    loggerParams.useTimestamp = true;
    loggerParams.logToConsole = true;
    Logger::Init(loggerParams);
    Logger::Log("Hello\n");
    Logger::Log("Test number: %i\n", 10);
    Logger::Log("Test complex: %s %i %f\n", "test string", 50, 1.5);
    return 0;
}

If the above code was in a file called `main.cpp` and `Logger` was installed following the instructions above, on a Linux system you should be able to compile this example with:
g++ main.cpp -o main -lLogger

