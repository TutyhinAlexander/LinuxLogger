#include "Logger.h"
#include <stdarg.h>
#include <ctime>
#include <memory.h>
#include <string>
#include <dirent.h>

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

	void Logger::Init(LoggerParams& initParams)
	{
		Logger logger = getInstance();
		logger.useTimestamp = initParams.useTimestamp;
		logger.logToConsole = initParams.logToConsole;
		if(logger.useTimestamp)
			tzset();

		if(initParams.fileName)
		{
			std::string logPath = "./Logs/";
			logPath.append(initParams.fileName);
			if(initParams.maxLogFiles > 1)
			{
				/*struct dirent** namelist;
				int n;

				n = scandir(".", &namelist, NULL, alphasort);
				if (n < 0)
					perror("scandir");
				else {
					while (n--) {
						printf("%s\n", namelist[n]->d_name);
						free(namelist[n]);
					}
					free(namelist);
				}*/

/*
				logPath.append("_[");
				strdate(logger.timebuf, 9);
				logPath.append(logger.timebuf);
				logPath.append("_");
				strtime(logger.timebuf, 128);
				logPath.append(logger.timebuf);
				logPath.append("].txt");
				*/

				//Logger::Log("logPath: '%s'\n", logPath.c_str());
				

				/*
				List<string> filesArr = Directory.GetFiles(logPath, appName + "_*.txt").ToList();
				filesArr.Sort();

				if (filesArr.Count > 9)
					File.Delete(filesArr[0]);
				logPath = Path.Combine(logPath, fileName);
				*/
			}
			else
				logPath.append(".txt");
			//getInstance().logFile = fopen(logPath.c_str(), "w");
		}
	}

	void Logger::Log(const char* msg, ...)
	{
		Logger logger = getInstance();
		if (logger.useTimestamp)
		{
			time_t timestamp = time(NULL);
			struct tm datetime = *localtime(&timestamp);
			strftime(logger.timebuf, 50, "%Y-%b-%d_%H:%M:%S", &datetime);
			//_strtime_s(logger.timebuf, 128);

			if(logger.logFile)
				//fprintf(logger.logFile, "[%i] ", tm.tm_year);
				fprintf(logger.logFile, "[%s] ", logger.timebuf);

			if(logger.logToConsole)
				//printf("[%i] ", tm.tm_year);
				printf("[%s] ", logger.timebuf);
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

