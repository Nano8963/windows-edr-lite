#include "detection_engine.h"

#include <stdio.h>
#include <string.h>

#include "logger.h"

static const ProcessInfo *find_process_by_pid(const ProcessInfo processes[],
                                              int process_count,
                                              DWORD pid)
{
    int i;

    for (i = 0; i < process_count; i++) {
        if (processes[i].pid == pid) {
            return &processes[i];
        }
    }

    return NULL;
}

static int process_name_equals(const char *left, const char *right)
{
    return _stricmp(left, right) == 0; //Function for making process names case insensitive
}

static int command_line_contains_encoded_flag(const ProcessInfo *process)
{
    (void)process;

    /*
     * Placeholder for future command-line capture:
     * ProcessInfo currently stores only PID, parent PID, and executable name.
     * To detect powershell.exe -enc, the process collector must also capture
     * each process command line and store it in ProcessInfo.
     */
    return 0;
}

int run_detection_rules(const ProcessInfo processes[], int process_count)
{
    int i;
    int alert_count = 0;

    if (processes == NULL || process_count <= 0) {
        log_warn("No process records were provided to the detection engine.");
        return 0;
    }

    log_info("Running simple detection rules.");

    for (i = 0; i < process_count; i++) {
        const ProcessInfo *child = &processes[i];
        const ProcessInfo *parent = find_process_by_pid(processes,
                                                        process_count,
                                                        child->parent_pid);

        if (parent != NULL &&
            process_name_equals(parent->exe_name, "WINWORD.EXE") &&
            process_name_equals(child->exe_name, "powershell.exe")) {
            printf("[ALERT] WINWORD.EXE launched powershell.exe "
                   "(parent PID: %lu, child PID: %lu)\n",
                   parent->pid,
                   child->pid);
            alert_count++;
        }

        if (parent != NULL &&
            process_name_equals(parent->exe_name, "EXCEL.EXE") &&
            process_name_equals(child->exe_name, "cmd.exe")) {
            printf("[ALERT] EXCEL.EXE launched cmd.exe "
                   "(parent PID: %lu, child PID: %lu)\n",
                   parent->pid,
                   child->pid);
            alert_count++;
        }

        // This is for the command line capture that isn't implemented yet
        if (process_name_equals(child->exe_name, "powershell.exe") &&
            command_line_contains_encoded_flag(child)) {
            printf("[ALERT] powershell.exe command line contains -enc "
                   "(PID: %lu)\n",
                   child->pid);
            alert_count++;
        }
    }

    if (alert_count == 0) {
        log_info("No alerts matched the current process list.");
    }

    return alert_count;
}
