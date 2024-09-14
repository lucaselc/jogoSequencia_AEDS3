#include <stdio.h>
#include <stdlib.h>
#include "instant.h"

instant now() {
    instant now;
    getrusage(RUSAGE_SELF, &now.ru);
    gettimeofday(&now.time, NULL);
    return now;
}

static double seconds_since(struct timeval now, struct timeval then) {
    return now.tv_sec - then.tv_sec + (now.tv_usec - then.tv_usec) / 1000000.0;
}

void print_time_elapsed(instant now, instant then) {
    double user = seconds_since(now.ru.ru_utime, then.ru.ru_utime);
    double system = seconds_since(now.ru.ru_stime, then.ru.ru_stime);
    double clock = seconds_since(now.time, then.time);

    if(getenv("TP2_MACHINE") == NULL) {
        printf("Tempo de usuário: %.8lf\n", user);
        printf("Tempo de sistema: %.8lf\n", system);
        printf("Tempo de relógio: %.8lf\n", clock);
    } else {
        printf("%lf\n", user);
        printf("%lf\n", system);
        printf("%lf\n", clock);
    }
}

