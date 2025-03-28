#include "Logger.h"
#include <stdarg.h>
#include <ctime>
#include <memory.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h> 

namespace DebugTools
{
	Logger::~Logger()
	{
		if(getInstance().logFile)
			fclose(getInstance().logFile);
	}

	Logger& Logger::getInstance()
	{
		static Logger instance;
		return instance;
	}
	
	void Logger::OpenLogFile(const char* fileName, int maxLogFiles)
	{
		const char* logsDir = "./Logs/";
		std::string logPath = logsDir;
		struct stat st;
		// check if Logs dir exist
		if ((stat(logsDir, &st) == 0) && (((st.st_mode) & S_IFMT) == S_IFDIR))
		{
			//Log("'%s' is present\n", logsDir);
			struct dirent** namelist;
			int n = scandir(logsDir, &namelist, NULL, alphasort);
			if (n < 0)
			{
				perror("scandir");
				return;
			}
			else 
			{
				// delete old logs
				int logCounter = 0;
				while (n--) 
				{
					if(namelist[n]->d_type == DT_REG) // test if item is a file
					{
						//Log("file: %s\n", namelist[n]->d_name);
						std::string fn = namelist[n]->d_name;
						if(fn.find(fileName) == 0)
						{
							++logCounter;
							//Log("find logFile logCounter=%i\n", logCounter);
							if(logCounter >= maxLogFiles)
							{
								fn.insert(0, logPath);
								std::remove(fn.c_str());
								//Log("file '%s' was removed\n", fn.c_str());
							}
						}
					}
					free(namelist[n]);
				}
				free(namelist);
			}
			
		}
		else // need create Logs dir
		{
			if(mkdir(logsDir, 0755) != 0)
			{
				perror("mkdir");
				return;
			}
			Log("'%s' was created\n", logsDir);
		}
		
		logPath.append(fileName);
		time_t timestamp = time(NULL);
		struct tm datetime = *localtime(&timestamp);
		strftime(timebuf, 50, "_[%Y-%b-%d_%H:%M:%S].txt", &datetime);
		logPath.append(timebuf);

		Log("logPath: '%s'\n", logPath.c_str());
		logFile = fopen(logPath.c_str(), "w");
	}

	void Logger::Init(LoggerParams& initParams)
	{
		Logger logger = getInstance();
		logger.useTimestamp = initParams.useTimestamp;
		logger.logToConsole = initParams.logToConsole;
		if(logger.useTimestamp)
			tzset();

		if(initParams.fileName)
			logger.OpenLogFile(initParams.fileName, initParams.maxLogFiles);
	}

	void Logger::Log(const char* msg, ...)
	{
		Logger logger = getInstance();
		if (logger.useTimestamp)
		{
			time_t timestamp = time(NULL);
			struct tm datetime = *localtime(&timestamp);
			strftime(logger.timebuf, 50, "[%Y-%b-%d_%H:%M:%S]", &datetime);

			if(logger.logFile)
				fprintf(logger.logFile, "%s ", logger.timebuf);

			if(logger.logToConsole)
				printf("%s ", logger.timebuf);
		}

		va_list args;
		va_start(args, msg);
		if (logger.logFile)
		{
			vfprintf(logger.logFile, msg, args);
			fflush(logger.logFile);
		}

		if (logger.logToConsole)
			vprintf(msg, args);

		va_end(args);
	}
}

