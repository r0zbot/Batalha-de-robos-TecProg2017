#ifndef VIRTUALMACHINE_LOG_H
#define VIRTUALMACHINE_LOG_H

#include <string>

using namespace std;

class Log {

    public:
        static void debug(const string &msg);
        static void info (const string &msg);
        static void warn (const string &msg);
        static void error(const string &msg);
};

#endif
