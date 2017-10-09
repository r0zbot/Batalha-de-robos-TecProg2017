#include <config.h>
#include <log.h>

void Log::debug(const string &msg) {
    if(Log::LOGGING_LEVEL<=Log::DEBUG) fprintf(stdout, "<DEBUG> %s\n", msg.c_str());
}

void Log::error(const string &msg) {
    if(Log::LOGGING_LEVEL<=Log::ERROR) fprintf(stderr, "<ERROR> %s\n", msg.c_str());
    abort();
}

void Log::info(const string &msg) {
    if(Log::LOGGING_LEVEL<=Log::INFO) fprintf(stdout, "<INFO> %s\n", msg.c_str());
}

void Log::warn(const string &msg) {
    if(Log::LOGGING_LEVEL<=Log::WARN) fprintf(stderr, "<WARN> %s\n", msg.c_str());
}
