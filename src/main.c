#include <stdio.h>

#include "logger.h"

int main(void)
{
    printf("========================================\n");
    printf(" Windows EDR Lite - Milestone 1\n");
    printf("========================================\n\n");

    log_info("Application started.");
    log_warn("Advanced EDR logic is not implemented yet.");
    log_error("Example error log entry.");

    return 0;
}

