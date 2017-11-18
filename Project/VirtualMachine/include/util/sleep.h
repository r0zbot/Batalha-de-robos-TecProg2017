//
// Created by Daniel on 17/11/2017.
//

#ifndef VIRTUALMACHINE_SLEEP_H
#define VIRTUALMACHINE_SLEEP_H

#ifdef linux
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

void arena_sleep(unsigned int sleepMs) {
#ifdef linux
    usleep(sleepMs * 1000);
#endif
#ifdef _WIN32
    Sleep(sleepMs);
#endif
}

#endif //VIRTUALMACHINE_SLEEP_H
