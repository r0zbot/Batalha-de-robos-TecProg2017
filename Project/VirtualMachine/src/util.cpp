#include "../include/util.h"

static void error(const string& msg) {
    fprintf(stderr,"%s\n", msg.c_str());
}

static void fatal(const string& msg, int cod) {
    error(msg);
    exit(cod);
}