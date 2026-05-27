#ifndef WINDOWS_EDR_LITE_PROCESS_MONITOR_H
#define WINDOWS_EDR_LITE_PROCESS_MONITOR_H

#include <windows.h>

typedef struct ProcessInfo {
    DWORD pid;
    DWORD parent_pid;
    char exe_name[MAX_PATH];
} ProcessInfo;

int get_running_processes(ProcessInfo processes[], int max_processes);

#endif
