#include "process_monitor.h"

#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

#include "logger.h"

void list_running_processes(void)
{
    /*
     * CreateToolhelp32Snapshot asks Windows for a list of
     * processes. TH32CS_SNAPPROCESS includes all processes in the system in the snapshot.
     */
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        log_error("Could not create a process snapshot.");
        return;
    }

    /*
     * PROCESSENTRY32 holds information about one process at a time.
     * Windows requires dwSize to be set before calling Process32First.
     */
    PROCESSENTRY32 process_entry;
    process_entry.dwSize = sizeof(PROCESSENTRY32);

    /*
     * Process32First reads the first process from the snapshot.
     * If it fails, there is nothing useful to print.
     */
    if (!Process32First(snapshot, &process_entry)) {
        log_error("Could not read the first process from the snapshot.");
        CloseHandle(snapshot);
        return;
    }

    printf("\nRunning Processes\n");
    printf("------------------------------------------------------------\n");
    printf("%-32s %-10s %-10s\n", "Process Name", "PID", "Parent PID");
    printf("------------------------------------------------------------\n");

    /*
     * This loop prints the current process entry, then asks Windows for
     * the next one. Process32Next returns FALSE when there are no more.
     */
    do {
        printf("%-32s %-10lu %-10lu\n",
               process_entry.szExeFile,
               process_entry.th32ProcessID,
               process_entry.th32ParentProcessID);
    } while (Process32Next(snapshot, &process_entry));

    /*
     * Every successful CreateToolhelp32Snapshot call gives us a handle.
     * CloseHandle releases it when we are done.
     */
    CloseHandle(snapshot);
}
