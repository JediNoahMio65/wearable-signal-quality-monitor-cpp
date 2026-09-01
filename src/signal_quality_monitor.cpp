#include "../include/signal_quality_monitor.hpp"

SignalQualityMonitor::SignalQualityMonitor()
    : state_(SignalQualityState::GOOD),
    good_amplitude_threshold_(0.70),
    degraded_amplitude_threshold_(0.40),
    high_motion_threshold_(0.60),
    consecutive_good_samples_(0),
    required_recovery_samples_(2) {
}

void SignalQualityMonitor::update(const SensorSample& sample) {
    const bool invalid_signal =
        !sample.sensor_connected ||
        sample.ppg_amplitude < degraded_amplitude_threshold_ ||
        sample.motion_level > high_motion_threshold_;

    const bool degraded_signal =
        sample.ppg_amplitude < good_amplitude_threshold_;

    if (invalid_signal) {
        state_ = SignalQualityState::INVALID;
        consecutive_good_samples_ = 0;
        return;
    }

    if (state_ == SignalQualityState::INVALID ||
        state_ == SignalQualityState::RECOVERING) {
        if (!degraded_signal) {
            ++consecutive_good_samples_;

            if (consecutive_good_samples_ >= required_recovery_samples_) {
                state_ = SignalQualityState::GOOD;
                consecutive_good_samples_ = 0;
            }
            else {
                state_ = SignalQualityState::RECOVERING;
            }
        }
        else {
            state_ = SignalQualityState::DEGRADED;
            consecutive_good_samples_ = 0;
        }

        return;
    }

    if (degraded_signal) {
        state_ = SignalQualityState::DEGRADED;
        consecutive_good_samples_ = 0;
        return;
    }

    state_ = SignalQualityState::GOOD;
    consecutive_good_samples_ = 0;
}

SignalQualityState SignalQualityMonitor::get_state() const {
    return state_;
}

bool SignalQualityMonitor::is_heart_rate_output_allowed() const {
    return state_ == SignalQualityState::GOOD ||
        state_ == SignalQualityState::DEGRADED;
}