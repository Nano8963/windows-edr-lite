#ifndef WINDOWS_EDR_LITE_DETECTION_ENGINE_H
#define WINDOWS_EDR_LITE_DETECTION_ENGINE_H

#include "process_monitor.h"

int run_detection_rules(const ProcessInfo processes[], int process_count);

#endif
