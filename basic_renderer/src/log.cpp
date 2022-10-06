//this document is basically a perfect copy of https://github.com/m100re 's logger, and I hearby thank him for letting me use it!

#include <iostream>
#include <ctime>

#include "log.h"

#ifdef _WIN32
#include <Windows.h>
#endif

logger::logger(LOG_TYPE log_type, const char* file, const char* function, int line)
#ifdef _WIN32
    : log_type(log_type)
#endif
{
#ifndef _WIN32
    const char* format = "";

    switch (log_type)
    {
        case MM_LOG_TYPE_INFO: format = "\e[38;42mINFO :: "; break;
        case MM_LOG_TYPE_FATAL: format = "\e[48;5;196;1mFATAL :: "; break;
        case MM_LOG_TYPE_WARNING: format = "\e[38;5;220mWARNING :: "; break;
        case MM_LOG_TYPE_TRACE: format = "\e[38;5;240mTRACE :: "; break;
        case MM_LOG_TYPE_ERROR: format = "\e[38;5;196;1mERROR :: "; break;
    }
#endif

    time_t current_time = time(0);

#ifdef _WIN32
    tm ltm;
    localtime_s(&ltm, &current_time);

    date << "[" << ltm.tm_mday << "-" << ltm.tm_mon << "-" << ltm.tm_year + 1900 << " | " << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << "] - ";

    const char* type = "";
    switch (log_type)
    {
    case LOG_TYPE_INFO: type = "INFO :: "; break;
    case LOG_TYPE_FATAL: type = "FATAL :: "; break;
    case LOG_TYPE_WARNING: type = "WARNING :: "; break;
    case LOG_TYPE_TRACE: type = "TRACE :: "; break;
    case LOG_TYPE_ERROR: type = "ERROR :: "; break;
    }
    message_stream << type;

    message_stream << file << "\\" << function << ":" << line << " -> ";
#else
    auto ltm = *std::localtime(&current_time);

    message_stream << "[" << ltm.tm_mday << "-" << ltm.tm_mon << "-" << ltm.tm_year + 1900 << " | " << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << "] - ";
    message_stream << format << file << "/" << function << ":" << line << " -> ";
#endif
}

logger::~logger()
{
#ifdef _WIN32
    message_stream << "\n";
    std::cout << date.str();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int color = 0;

    switch (log_type)
    {
        case LOG_TYPE_INFO: color = 2; break;
        case LOG_TYPE_FATAL: color = 79; break;
        case LOG_TYPE_WARNING: color = 6; break;
        case LOG_TYPE_TRACE: color = 8; break;
        case LOG_TYPE_ERROR: color = 12; break;
    }

    SetConsoleTextAttribute(hConsole, color);

    std::cout << message_stream.str();

    SetConsoleTextAttribute(hConsole, 7);
#else
    message_stream << "\e[0m\n";
    std::cout << message_stream.str();
#endif
} 