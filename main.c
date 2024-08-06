#include <stdio.h>
#include <time.h>
#include <math.h>

int main(void) {
    time_t CURRENT_TIME = time(NULL);
    struct tm *CURRENT_GMT = gmtime(&CURRENT_TIME);
    // BEAT is calculated at GMT+1 (CET)
    int hour = CURRENT_GMT -> tm_hour + 1;
    int minute = CURRENT_GMT -> tm_min;
    int second = CURRENT_GMT -> tm_sec;
    int beat = floor((3600 * hour + 60 * minute + second) / 86.4);
    printf("@%d", beat);
    return 0;
}
