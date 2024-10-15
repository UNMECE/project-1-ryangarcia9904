#ifndef CAPACITOR_H
#define CAPACITOR_H

//Capacitor Struct
struct _capacitor {
    double *time;       // time array
    double *voltage;    // voltage array
    double *current;    // current array
    double C;           // capacitance value
};
typedef struct _capacitor Capacitor;

//Calling Functions
void initializeCapacitor(Capacitor &cap, double finalTime, double deltaT, double R, double C, double initialCurrent, double initialVoltage);
void simulateCapacitor(Capacitor &cap, double deltaT, double R, int numTimesteps);
void freeMemory(Capacitor &cap);

#endif