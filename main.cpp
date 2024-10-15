#include <iostream>
#include <iomanip>
#include "capacitor.h"

void initializeCapacitor(Capacitor &cap, double finalTime, double deltaT, double R, double C, double initialCurrent, double initialVoltage) {
    int numTimesteps = static_cast<int>(finalTime / deltaT);
    cap.time = new double[numTimesteps];
    cap.voltage = new double[numTimesteps];
    cap.current = new double[numTimesteps];
    
    // Set initial conditions
    cap.time[0] = 0.0;
    cap.voltage[0] = initialVoltage;
    cap.current[0] = initialCurrent;

    for (int i = 1; i < numTimesteps; ++i) {
        cap.time[i] = cap.time[i - 1] + deltaT;
    }
    
    cap.C = C;
}

void simulateCapacitor(Capacitor &cap, double deltaT, double R, int numTimesteps) {
    for (int t = 1; t < numTimesteps; ++t) {
        // Update voltage and current using the given equations
        cap.voltage[t] = cap.voltage[t - 1] + (cap.current[t - 1] * deltaT / cap.C);
        cap.current[t] = cap.current[t - 1] - (cap.current[t - 1] / (R * cap.C) * deltaT);

        // Output results every 200 timesteps
        if (t % 200 == 0) {
            std::cout << std::fixed << std::setprecision(6);
            std::cout << "Time: " << cap.time[t] << " s, Voltage: " << cap.voltage[t]
                      << " V, Current: " << cap.current[t] << " A" << std::endl;
        }
    }
}

void freeMemory(Capacitor &cap) {
    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;
}

int main() {
    // Constants
    const double deltaT = 1e-10;       // Time step
    const double finalTime = 5e-6;     // Final time
    const double R = 1e3;               // Resistance in ohms (1 kΩ)
    const double C = 100e-12;           // Capacitance in farads (100 pF)
    const double I0 = 1e-2;              // Initial current (10 mA)
    const double V0 = 10.0;              // Initial voltage (10 V)

    Capacitor cap;
    initializeCapacitor(cap, finalTime, deltaT, R, C, I0, V0);
    int numTimesteps = static_cast<int>(finalTime / deltaT);

    simulateCapacitor(cap, deltaT, R, numTimesteps);
    freeMemory(cap);

    return 0;
}
