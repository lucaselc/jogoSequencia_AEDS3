#pragma once
#include <sys/resource.h>
#include <sys/time.h>

typedef struct {
    struct rusage ru;
    struct timeval time;
}instant;


instant now();
void print_time_elapsed(instant now, instant then);
