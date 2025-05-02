#ifndef __LOGGER_H_
#define __LOGGER_H_

#include <string>
#include <stdio.h>
#include <queue>
#include <mutex>

#ifdef LOG_OFF
	#define LOG(...) 
#else
	#define LOG(...) Logger::Log(__VA_ARGS__)	
#endif // LOG_OFF

namespace DebugTools
{
	struct LoggerParams
	{
		bool useTimestamp = false;
		bool logToConsole = true;
		const char* fileName = NULL;
		int maxLogFiles = 1; // if > 1 then each run a new log file will be created until reach maxLogFiles. After will rewrite first file.
	};
	
		
	class Logger
	{
	private:
		static Logger instance;
		bool inited = false;
		bool finish = false;
		LoggerParams params;
		FILE* logFile = NULL;
		char msgbuf[255];
		bool useTimestamp = false;
		bool logToConsole = true;
		std::queue<std::string> messagesQueue;
		std::mutex msgQueueMutex;

		static Logger& getInstance();
		void OpenLogFile(const char* fileName, int maxLogFiles);
		void ProcessQueueMessage();
	
	public:
		~Logger();

		static void Init(LoggerParams& initParams);
		static void Log(const char* msg, ...);
	};
}

#endif // __LOGGER_H_
