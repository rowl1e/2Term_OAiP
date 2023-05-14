#ifndef TASKS_H
#define TASKS_H

#include "header.h"

void arrayCreation (monitor_t** monitors, int* n);
void monitorFilling (monitor_t** monitors, int* n, int i);
void addMonitors (monitor_t** monitors, int* n);
void addMonitors1st (monitor_t** monitors, int* n);
void deletingMonitor (monitor_t** monitors, int* n);

int compareMonitorType (monitor_t* first, monitor_t* second);
int compareProducer (monitor_t* first, monitor_t* second);
int compareRefreshRate (monitor_t* first, monitor_t* second);
int compareScreenSize (monitor_t* first, monitor_t* second);
int compareResolution (monitor_t* first, monitor_t* second);
int comparePrice (monitor_t* first, monitor_t* second);
int compare (monitor_t* first, monitor_t* second, int field);

void insertionSort (monitor_t* monitors, int n, int firstField, int secondField);
void sortByTwo (monitor_t** monitors, int* n);

void printMonitors (monitor_t** monitors, int* n);

#endif //TASKS_H