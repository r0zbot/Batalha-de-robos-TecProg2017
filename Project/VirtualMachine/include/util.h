#ifndef VIRTUALMACHINE_UTIL_H
#define VIRTUALMACHINE_UTIL_H

#include <string>

using namespace std;

static void error(const string& msg);
static void fatal(const string& msg, int cod);

#endif
