#include "Logger/Logger.h"
#include <stdarg.h>
#include <ctime>
#include <memory.h>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

namespace DebugTools
{
	Logger Logger::instance;
	
	Logger::~Logger()
	{
		if(getInstance().logFile)
			fclose(getInstance().logFile);
	}

	Logger& Logger::getInstance()
	{
		return instance;
	}
	
	void Logger::OpenLogFile(const char* fileName, int maxLogFiles)
	{
		const char* logsDir = "./Logs/";
		std::string logPath = logsDir;
		// check if Logs dir exist
		if (std::filesystem::exists(logsDir))
		{
			int logCounter = 0;
			vector<fs::path> filesInDir;
			copy(fs::directory_iterator(logsDir), fs::directory_iterator(), back_inserter(filesInDir));
			std::sort(filesInDir.rbegin(), filesInDir.rend());

			for (const string& filename : filesInDir)
			{
				fs::path p(filename);
				if(!is_regular_file(p) || !p.filename().string().find(fileName) == 0) // not a file or some other then log template file
					continue;
					
				++logCounter;
				//Log("find logFile logCounter=%i filename='%s'\n", logCounter, filename.c_str());
				// delete old logs					
				if(logCounter >= maxLogFiles)
				{
					fs::remove(p);
					//Log("file '%s' was removed\n", filename.c_str());
				}				
			}
		}
		else // need create Logs dir
		{
			if(!fs::create_directory(logsDir))
			{
				Log("Can't create '%s' dirrectory!\n", logsDir);
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
		Logger& logger = getInstance();
		logger.useTimestamp = initParams.useTimestamp;
		logger.logToConsole = initParams.logToConsole;
		if(logger.useTimestamp)
			tzset();

		if(initParams.fileName)
			logger.OpenLogFile(initParams.fileName, initParams.maxLogFiles);
	}

	void Logger::Log(const char* msg, ...)
	{
		Logger& logger = getInstance();
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

