#include "logger.h"

#include <stdio.h>

static void log_message(const char *level, const char *message)
{
    printf("[%s] %s\n", level, message);
}

void log_info(const char *message)
{
    log_message("INFO", message);
}

void log_warn(const char *message)
{
    log_message("WARN", message);
}

void log_error(const char *message)
{
    log_message("ERROR", message);
}
