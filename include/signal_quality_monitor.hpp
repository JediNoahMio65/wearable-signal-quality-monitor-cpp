#pragma once

#include "sensor_sample.hpp"

enum class SignalQualityState {
    GOOD,
    DEGRADED,
    INVALID,
    RECOVERING
};

class SignalQualityMonitor {
public:
    SignalQualityMonitor();

    void update(const SensorSample& sample);

    SignalQualityState get_state() const;

    bool is_heart_rate_output_allowed() const;

private:
    SignalQualityState state_;

    double good_amplitude_threshold_;
    double degraded_amplitude_threshold_;
    double high_motion_threshold_;

    int consecutive_good_samples_;
    int required_recovery_samples_;
};