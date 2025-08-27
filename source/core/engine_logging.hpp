#include <stdio.h>

typedef enum {
    LOG,
    DEBUG,
    WARNING,
    ERROR,
    FATAL
} severities;

static void log(const char* log_info, severities severity = LOG) {
    switch (severity) {
        case LOG:
            printf("\033[37m[LOG] %s\033[0m", log_info);
            break;
        case DEBUG:
            printf("\033[32m[DEBUG] %s\033[0m", log_info);
            break;
        case WARNING:
            printf("\033[33m[WARNING] %s\033[0m", log_info);
            break;
        case ERROR:
            printf("\033[31m[ERROR] %s\033[0m", log_info);
            break;
        case FATAL:
            printf("\033[41m\033[37m[FATAL] %s\033[0m\033[K", log_info);
            break;
    }
}