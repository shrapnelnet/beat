#include <stdio.h>
#include <time.h>

// number of seconds in an hour, a day and a swatch beat
#define ONE_HOUR 3600
#define ONE_DAY 86400
#define ONE_BEAT 86.4

int main(void) {
    time_t CURRENT_TIME = time(NULL);
    const int oneHour = 3600;
    const int oneDay = 86400;
    int beat = ((CURRENT_TIME + ONE_HOUR) % ONE_DAY ) / ONE_BEAT;
    printf("@%d\n", beat);
    return 0;
}
