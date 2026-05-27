#include "process_monitor.h"

#include <stdio.h>
#include <tlhelp32.h>

#include "logger.h"

int get_running_processes(ProcessInfo processes[], int max_processes)
{
    int process_count = 0;

    if (processes == NULL || max_processes <= 0) {
        log_error("Invalid process array provided.");
        return 0;
    }

    /*
     * CreateToolhelp32Snapshot asks Windows for a list of
     * processes. TH32CS_SNAPPROCESS includes all processes in the system in the snapshot.
     */
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        log_error("Could not create a process snapshot.");
        return 0;
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
        return 0;
    }

    /*
     * This loop copies each Windows process entry into our own beginner-friendly
     * ProcessInfo struct array. The loop stops when the array is full or when
     * Windows reports that there are no more processes.
     */
    do {
        processes[process_count].pid = process_entry.th32ProcessID;
        processes[process_count].parent_pid = process_entry.th32ParentProcessID;

        /*
         * snprintf safely copies the executable name into exe_name.
         * MAX_PATH is the size of the destination buffer.
         */
        snprintf(processes[process_count].exe_name,
                 MAX_PATH,
                 "%s",
                 process_entry.szExeFile);

        process_count++;
    } while (process_count < max_processes && Process32Next(snapshot, &process_entry));

    /*
     * Every successful CreateToolhelp32Snapshot call gives us a handle.
     * CloseHandle releases it when we are done.
     */
    CloseHandle(snapshot);

    return process_count;
}
