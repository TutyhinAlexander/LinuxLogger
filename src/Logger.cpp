#include "Logger/Logger.h"
#include <stdarg.h>
#include <ctime>
#include <memory.h>
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
		if(logFile)
			fclose(logFile);
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
				//LOG("find logFile logCounter=%i filename='%s'\n", logCounter, filename.c_str());
				// delete old logs					
				if(logCounter >= maxLogFiles)
				{
					fs::remove(p);
					//LOG("file '%s' was removed\n", filename.c_str());
				}				
			}
		}
		else // need create Logs dir
		{
			if(!fs::create_directory(logsDir))
			{
				LOG("Can't create '%s' dirrectory!\n", logsDir);
				return;
			}
			LOG("'%s' was created\n", logsDir);
		}
		
		logPath.append(fileName);
		time_t timestamp = time(NULL);
		struct tm datetime = *localtime(&timestamp);
		strftime(msgbuf, 50, "_[%Y-%b-%d_%H:%M:%S].txt", &datetime);
		logPath.append(msgbuf);

		LOG("logPath: '%s'\n", logPath.c_str());
		logFile = fopen(logPath.c_str(), "w");
	}

	void Logger::Init(LoggerParams& initParams)
	{
		Logger& logger = getInstance();
		logger.inited = true;
		logger.useTimestamp = initParams.useTimestamp;
		logger.logToConsole = initParams.logToConsole;
		if(logger.useTimestamp)
			tzset();

		if(initParams.fileName && *initParams.fileName != '\0')
			logger.OpenLogFile(initParams.fileName, initParams.maxLogFiles);
	}

	void Logger::Log(const char* msg, ...)
	{
		Logger& logger = getInstance();
		if(!logger.inited)
			return;

		size_t len = 0;
		{// additional scope for limiting lock time of lock_guard 
			lock_guard<std::mutex> lock(logger.msgQueueMutex);			
			if (logger.useTimestamp)
			{
				time_t timestamp = time(NULL);
				struct tm datetime = *localtime(&timestamp);
				len = strftime(logger.msgbuf, 50, "[%Y-%b-%d_%H-%M-%S] ", &datetime);
			}
			
			va_list args;
			va_start(args, msg);
			vsprintf(logger.msgbuf + len, msg, args);
			va_end(args);
		
			logger.messagesQueue.push(string(logger.msgbuf));
			len = logger.messagesQueue.size();
		}

		if(len == 1)
			logger.ProcessQueueMessage();
	}
	
	void Logger::ProcessQueueMessage()
	{
		unique_lock<mutex> queueLock(msgQueueMutex);
		string msg = messagesQueue.front();
		queueLock.unlock();
		
		if (logFile)
		{
			fprintf(logFile, msg.c_str());
			fflush(logFile);
		}
		
		if (logToConsole)
			printf(msg.c_str());
			
		queueLock.lock();
		messagesQueue.pop();
		bool isEmpty = messagesQueue.empty();
		queueLock.unlock();
		if(!isEmpty)
			ProcessQueueMessage();
	}
}

