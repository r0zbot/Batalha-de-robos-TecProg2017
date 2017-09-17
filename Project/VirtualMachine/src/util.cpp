#include "../include/util.h"


//TODO: com string ele da erro na dll. Com char* ele da warning, o que fazer?
static void error(char *msg) {
    fprintf(stderr, "%s\n", msg);
}

static void fatal(char *msg, int cod) {
    error(msg);
    exit(cod);
}
