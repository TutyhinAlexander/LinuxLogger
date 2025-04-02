# LinuxLogger

Stream logger for development under linux

## Description

Stream logger, supports output into file and console

## Installation

### Linux

1. If no `git` installed, install it:

	```bash
	$ sudo apt install git
	```	

1. Make sure you have cmake installed. If no - install it:

	```bash
	$ sudo apt-get -y install cmake
	```	

1. Create and enter directory for project to install into

	```bash
	$ mkdir Logger
	$ cd Logger
	```	

1. Clone project onto your current directory

	```bash
	$ git clone https://github.com/TutyhinAlexander/LinuxLogger.git .
	```	

1. Create a new build directory and change into it:

	```bash
	$ mkdir build
	$ cd build
	```	

1. Run cmake on the parent directory to generate makefile:

	```bash
	$ cmake ..
	```

1. Run make on the generated makefile to generate the static library libLogger.a:

	```bash
	$ make
	```

1. To install the headers on your system:

	```bash
	$ sudo make install
	```	

## Using

1. Before start logging, you should call `Logger::Init(loggerParams);`
where `loggerParams` is a struct with logger settings:

    `loggerParams.fileName` - log file prefix (full file name will be in format <fileName>_[datatime].txt and it will 
	be stored in the './Logs' folder); if NULL - no file will be created
		
    `loggerParams.maxLogFiles` - log files limit in ./Logs folder
	
    `loggerParams.useTimestamp` - if true - before each message will be added [datatime]
	
    `loggerParams.logToConsole` - true if you need log to console

1. Start loging with `Logger::Log(msg, ...);`
 
	msg is printf like format string
	
## Using This Project As A CMake Dependency

Add folowwing to your main `CMakeLists.txt`:

```cmake
find_package(Logger REQUIRED)
...
...
target_link_libraries(<your_target_project> DebugTools::Logger)
```


## Examples

```c++
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
```		

If the above code was in a file called `main.cpp` and `Logger` was installed following the instructions above, on a Linux system you should be able to compile this example with:

```bash
g++ main.cpp -o main -lLogger
```	

