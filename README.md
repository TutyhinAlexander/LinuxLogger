# LinuxLogger
Stream logger for development under linux
Support output into file and console

LoggerLib - logger library
LoggerTest - example

For build LoggerTest:
	1)Inside LinuxLogger folder create build dir and enter it:
		mkdir build
		cd build
		
	2) Build LoggerTest:
		cmake ../
		cmake --build .
	3) Run LoggerTest from build folder:
		./LoggerTest


Usage:
1) Before start logging, you should call Logger::Init(loggerParams);
where loggerParams is a struct with logger params:
    loggerParams.fileName - log file prefix (full file name will be in format <fileName>_[datatime].txt and it will be stored in ./Logs folder);
	if NULL - no file will be created
    loggerParams.maxLogFiles - log files limit in ./Logs folder
    loggerParams.useTimestamp - if true - before each message will be added [datatime]
    loggerParams.logToConsole - tru if you need log to console
loggerParams can be local since it is not store in logger (see example)
2) Start loging with Logger::Log(msg, ...); msg is printf like format