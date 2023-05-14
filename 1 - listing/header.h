#ifndef HEADER_H
#define HEADER_H

typedef enum {
    gaming = 1,
    homeAndOffice,
    professional,
    other
} type_t;

typedef struct {
    type_t monitorType;
    char* producer;
    int refreshRate;
    float screenSize;
    int resolution[2];
    double price;
} monitor_t;

#endif //HEADER_H