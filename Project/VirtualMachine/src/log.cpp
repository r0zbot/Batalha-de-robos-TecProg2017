#include "log.h"

void Log::debug(const string &msg) {
    fprintf(stdout, "<DEBUG> %s\n", msg.c_str());
}

void Log::info(const string &msg) {
    fprintf(stdout, "<INFO> %s\n", msg.c_str());
}

void Log::warn(const string &msg) {
    fprintf(stderr, "<WARN> %s\n", msg.c_str());
}

void Log::error(const string &msg) {
    fprintf(stderr, "<ERROR> %s\n", msg.c_str());
    abort();
}
