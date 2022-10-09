#include <timer.h>
#include <interrupt.h>
#include <log.h>

unsigned int tick_counter = 0;
void tick(struct CPUState cpu, struct ErrorState error) {
    tick_counter++;
}

void timer_init() {
    set_handler(0, tick);
}

unsigned int timer_get_time() {
    return tick_counter;
}