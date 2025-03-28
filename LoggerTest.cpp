#include "Logger.h"

using namespace DebugTools;

int main()
{
    LoggerParams loggerParams;
    loggerParams.fileName = "FCA";
    loggerParams.maxLogFiles = 10;
    loggerParams.useTimestamp = true;
    loggerParams.logToConsole = true;
    Logger::Init(loggerParams);
    Logger::Log("Hello\n");
    Logger::Log("Test number: %i\n", 10);
    Logger::Log("Test complex: %s %i %f\n", "test string", 50, 1.5);
    return 0;
}
