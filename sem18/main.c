#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

volatile sig_atomic_t time = 0;
volatile sig_atomic_t did_alarm = 0;
volatile sig_atomic_t did_int = 0;
volatile sig_atomic_t last_time;

void handle_alarm(int signo) {
    did_alarm = 1;
    ++time;
}

void handle_interrupt(int signo) {
    if(!did_int) {
        ++did_int;
        last_time = time;
    } else {
        did_int = 3;
    }
}

int main(int argc, char **argv) {
    struct sigaction sa = {};
    sa.sa_handler = handle_alarm;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);
    sa.sa_handler = handle_interrupt;
    sigaction(SIGINT, &sa, NULL);
    alarm(1);
    while (1) {
        if(did_alarm) {
            did_alarm = 0;
            printf("%d\n", time);
            alarm(1);
        }
        if(did_int == 1) {
            puts("Start counter");
            ++did_int;
        } else if(did_int == 3){
            printf("%d\n", time-last_time);
            return 0;
        }
    }
}
