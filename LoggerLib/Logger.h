#ifndef __LOGGER_H_
#define __LOGGER_H_

#include <stdio.h>

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
		LoggerParams params;
		FILE* logFile = NULL;
		char timebuf[128];
		bool useTimestamp = false;
		bool logToConsole = true;

		static Logger& getInstance();
		void OpenLogFile(const char* fileName, int maxLogFiles);
	
	public:
		~Logger();

		static void Init(LoggerParams& initParams);
		static void Log(const char* msg, ...);
	};
}

#endif // __LOGGER_H_
