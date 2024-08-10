#include <stdio.h>
#include <time.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// number of seconds in an hour, a day and a swatch beat
#define ONE_HOUR 3600
#define ONE_DAY 86400
#define ONE_BEAT 86.4

/**
 * Calculate the current beat.
 * @return A short containing the current beat.
 */
short getCurrentBeat() {
    time_t CURRENT_TIME = time(NULL);
    return ((CURRENT_TIME + ONE_HOUR) % ONE_DAY) / ONE_BEAT;
}

void usage() {
    printf("Usage: beat [-u] UTC_OFFSET [-t] HH:MM:SS\n");
    exit(1);
}

int parseTimeAsSeconds(const char *time) {
    int hour;
    int minute;
    int second;
    char hourString[3];
    char minuteString[3];
    char secondString[3];
    if (strlen(time) != 8) {
        usage();
    }
    strncpy(hourString, time, 2);
    strncpy(minuteString, time + 3, 2);
    strncpy(secondString, time + 6, 2);
    hour = strtol(hourString, NULL, 10);
    minute = strtol(minuteString, NULL, 10);
    second = strtol(secondString, NULL, 10);
    if (hour > 24 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0) {
        usage();
    }
    return hour * 3600 + minute * 60 + second;
}

short getBeatAt(int argc, char *const argv[]) {
    int opt;
    struct ARGUMENTS {
        char *UTC_OFFSET;
        char *TIME;
    } parsedArgs;

    parsedArgs.UTC_OFFSET = NULL;
    parsedArgs.TIME = NULL;
    while ((opt = getopt(argc, argv, ":u:t:")) != -1) {
        switch (opt) {
            case 'u':
                parsedArgs.UTC_OFFSET = optarg;
                break;
            case 't':
                parsedArgs.TIME = optarg;
                break;
            case '?':
                if (optopt == 'u' || optopt == 't') {
                    fprintf(stderr, "Option -%c requires an argument\n", optopt);
                }
            default:
                usage();
        }
    }
    if (parsedArgs.UTC_OFFSET == NULL || parsedArgs.TIME == NULL) {
        usage();
    }
    int utcOffset = strtol(parsedArgs.UTC_OFFSET, NULL, 10) * 3600;
    int timeAsSeconds = parseTimeAsSeconds(parsedArgs.TIME);
    int timeAdjusted = utcOffset + timeAsSeconds;
    return ((timeAdjusted) % ONE_DAY) / ONE_BEAT;
}

int main(int argc, char *const argv[]) {
    bool hasArgs = argc > 1;
    short beat;
    if (!hasArgs) {
        beat = getCurrentBeat();
    } else {
        beat = getBeatAt(argc, argv);
    }
    printf("@%d\n", beat);
    return 0;
}
