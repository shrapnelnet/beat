#include <stdio.h>
#include <time.h>

int main(void) {
    time_t CURRENT_TIME = time(NULL);
    // +3600 cause swatch time is UTC + 1, % 86400 to have number of sec since midnight
    int beat = ((CURRENT_TIME + 3600) % 86400 ) / 86.4;
    printf("@%d\n", beat);
    return 0;
}
