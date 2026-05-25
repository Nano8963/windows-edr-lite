#include <stdio.h>

#include "logger.h"
#include "process_monitor.h"

static void print_startup_banner(void)
{
    printf("========================================\n");
    printf(" Windows EDR Lite\n");
    printf(" Process Enumeration Milestone\n");
    printf("========================================\n\n");
}

static void print_menu(void)
{
    printf("\nMenu\n");
    printf("1. List running processes\n");
    printf("0. Exit\n");
    printf("Select an option: ");
}

int main(void)
{
    char input[32];
    int choice = -1;

    print_startup_banner();
    log_info("Application started.");

    /*
     * Keep showing the menu until the user selects 0.
     * fgets reads one full line of input from the user.
     */
    while (choice != 0) {
        print_menu();

        /*
         * If fgets returns NULL, input was closed or an input error happened.
         * Treat that like a clean exit instead of looping forever.
         */
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            log_info("Input closed. Exiting application.");
            break;
        }

        /*
         * sscanf converts the text line into an integer menu choice.
         * If conversion fails, the user typed something that is not a number.
         */
        if (sscanf(input, "%d", &choice) != 1) {
            log_warn("Invalid input. Please enter a number.");
            choice = -1;
            continue;
        }

        if (choice == 1) {
            list_running_processes();
        } else if (choice == 0) {
            log_info("Exiting application.");
        } else {
            log_warn("Unknown menu option.");
        }
    }

    return 0;
}

