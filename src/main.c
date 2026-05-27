#include <stdio.h>

#include "detection_engine.h"
#include "logger.h"
#include "process_monitor.h"

#define MAX_PROCESS_RECORDS 1024

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
    printf("2. Run detection scan\n");
    printf("0. Exit\n");
    printf("Select an option: ");
}

static void print_processes(const ProcessInfo processes[], int process_count)
{
    int i;

    printf("\nRunning Processes\n");
    printf("------------------------------------------------------------\n");
    printf("%-32s %-10s %-10s\n", "Process Name", "PID", "Parent PID");
    printf("------------------------------------------------------------\n");

    /*
     * The process monitor collected the data.
     * This function is only responsible for displaying it.
     */
    for (i = 0; i < process_count; i++) {
        printf("%-32s %-10lu %-10lu\n",
               processes[i].exe_name,
               processes[i].pid,
               processes[i].parent_pid);
    }

    printf("\nTotal processes found: %d\n", process_count);
}

int main(void)
{
    char input[32];
    int choice = -1;
    ProcessInfo processes[MAX_PROCESS_RECORDS];

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
         */
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            log_info("Input closed. Exiting application.");
            break;
        }

        /*
         * sscanf converts the text line into an integer menu choice.
         * If conversion fails, a number was not entered.
         */
        if (sscanf(input, "%d", &choice) != 1) {
            log_warn("Invalid input. Please enter a number.");
            choice = -1;
            continue;
        }

        if (choice == 1) {
            int process_count = get_running_processes(processes, MAX_PROCESS_RECORDS);
            print_processes(processes, process_count);
        } else if (choice == 2) {
            int process_count = get_running_processes(processes, MAX_PROCESS_RECORDS);
            int alert_count = run_detection_rules(processes, process_count);

            printf("Detection scan complete. Alerts found: %d\n", alert_count);
        } else if (choice == 0) {
            log_info("Exiting application.");
        } else {
            log_warn("Unknown menu option.");
        }
    }

    return 0;
}

