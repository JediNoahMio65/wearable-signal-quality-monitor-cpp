#include <fstream>
#include <iostream>
#include <string>

#include "../include/sensor_sample.hpp"
#include "../include/signal_quality_monitor.hpp"

std::string state_to_string(SignalQualityState state) {
    switch (state) {
    case SignalQualityState::GOOD:
        return "GOOD";
    case SignalQualityState::DEGRADED:
        return "DEGRADED";
    case SignalQualityState::INVALID:
        return "INVALID";
    case SignalQualityState::RECOVERING:
        return "RECOVERING";
    default:
        return "UNKNOWN";
    }
}

int main() {
    SignalQualityMonitor monitor;

    SensorSample samples[] = {
        {0,    0.82, 0.05, true},
        {1000, 0.55, 0.10, true},
        {2000, 0.25, 0.75, true},
        {3000, 0.85, 0.05, true},
        {4000, 0.88, 0.04, true},
        {5000, 0.30, 0.10, true},
        {6000, 0.86, 0.05, true},
        {7000, 0.87, 0.05, true}
    };

    std::ofstream log_file("data/signal_quality_event_log.csv");

    if (!log_file.is_open()) {
        std::cerr << "Error: Unable to create event log file.\n";
        return 1;
    }

    log_file
        << "timestamp_ms,ppg_amplitude,motion_level,sensor_connected,"
        << "signal_quality_state,heart_rate_output\n";

    std::cout << "Wearable Signal-Quality Monitor Simulation\n";
    std::cout << "------------------------------------------\n";

    for (const SensorSample& sample : samples) {
        monitor.update(sample);

        const std::string state = state_to_string(monitor.get_state());
        const std::string output_allowed =
            monitor.is_heart_rate_output_allowed()
            ? "ALLOWED"
            : "SUPPRESSED";

        std::cout
            << "Time: " << sample.timestamp_ms << " ms"
            << " | PPG: " << sample.ppg_amplitude
            << " | Motion: " << sample.motion_level
            << " | State: " << state
            << " | HR output: " << output_allowed
            << "\n";

        log_file
            << sample.timestamp_ms << ","
            << sample.ppg_amplitude << ","
            << sample.motion_level << ","
            << (sample.sensor_connected ? "true" : "false") << ","
            << state << ","
            << output_allowed << "\n";
    }

    log_file.close();

    std::cout << "\nEvent log created: data/signal_quality_event_log.csv\n";

    return 0;
}