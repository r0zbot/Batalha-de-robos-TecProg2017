#include "../include/util.h"

static void error(string msg) {
    fprintf(stderr,"%s\n", msg);
}

static void fatal(string msg, int cod) {
    error(msg);
    exit(cod);
}