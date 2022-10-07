//this document is basically a perfect copy of https://github.com/m100re 's logger, and I hearby thank him for letting me use it!

#pragma once

#include <sstream>

enum LOG_TYPE
{
    LOG_TYPE_FATAL =    0,
    LOG_TYPE_ERROR =    1,
    LOG_TYPE_WARNING =  2,
    LOG_TYPE_TRACE =    3,
    LOG_TYPE_INFO =     4
};

class logger
    {
    private:
#ifdef _WIN32
        std::stringstream date;
        LOG_TYPE log_type;
#endif
        std::stringstream message_stream;
    public:
        logger(LOG_TYPE log_type, const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(), int line = __builtin_LINE());
        ~logger();

        template <typename T>
        logger& operator << (T argument)
        {
            message_stream << argument;
            return *this;
        }
    };

#define FATAL   logger(LOG_TYPE_FATAL)
#define ERROR   logger(LOG_TYPE_ERROR)
#define WARNING logger(LOG_TYPE_WARNING)
#define TRACE   logger(LOG_TYPE_TRACE)
#define INFO    logger(LOG_TYPE_INFO)