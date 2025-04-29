#include "Logger/Logger.h"
#include <thread>
#include <chrono>

using namespace DebugTools;

void GenerateMessagesThread()
{
    int counter = 50;
    while(--counter > 0)
    {
        LOG("Test string from thread: counter=%d\n", counter);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main()
{
    LoggerParams loggerParams;
    loggerParams.fileName = "Log";
    loggerParams.maxLogFiles = 10;
    loggerParams.useTimestamp = true;
    loggerParams.logToConsole = true;
    Logger::Init(loggerParams);
    LOG("Hello\n");
    LOG("Test number: %i\n", 10);
    LOG("Test complex: %s %i %f\n", "test string", 50, 1.5);

    std::thread msgThread_1 = std::thread(&GenerateMessagesThread);
    std::thread msgThread_2 = std::thread(&GenerateMessagesThread);
    
    msgThread_1.join();
    msgThread_2.join();        
    return 0;
}
