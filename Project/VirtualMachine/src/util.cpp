#include "../include/util.h"


static void error(const string& msg) {
    cout << msg << '\n';
}

static void fatal(const string& msg, int cod) {
    error(msg);
    exit(cod);
}
