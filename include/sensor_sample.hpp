#pragma once

struct SensorSample {
    int timestamp_ms;
    double ppg_amplitude;
    double motion_level;
    bool sensor_connected;
};