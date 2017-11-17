//
// Created by Daniel on 17/11/2017.
//

#ifndef VIRTUALMACHINE_SLEEP_H
#define VIRTUALMACHINE_SLEEP_H

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

void arena_sleep(int sleepMs) {
#ifdef LINUX
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}

#endif //VIRTUALMACHINE_SLEEP_H
