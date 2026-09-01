# Wearable Signal-Quality Monitor in C++

A C++17 console simulation of signal-quality monitoring and safe heart-rate-output behavior for a fictional wearable wellness device.

> **Simulation notice:** This project uses fictional sensor readings, signal-quality states, requirements, and test scenarios for educational portfolio purposes only. It is not medical-device software, clinical software, a diagnostic tool, or evidence of physiological performance.

## Objective

Demonstrate embedded-style C++ software architecture for processing simulated wearable sensor samples and controlling when a fictional heart-rate estimate may be displayed.

The monitor suppresses numerical heart-rate output when the simulated signal becomes invalid and requires two consecutive acceptable samples before output resumes.

## Implemented Behavior

```text
GOOD → DEGRADED → INVALID → RECOVERING → GOOD
```

- `GOOD`: Signal quality is acceptable; numerical heart-rate output is allowed.
- `DEGRADED`: Signal amplitude is below the preferred threshold but remains above the invalid threshold; output remains allowed.
- `INVALID`: Sensor is disconnected, PPG amplitude is too low, or motion exceeds the configured limit; output is suppressed.
- `RECOVERING`: First acceptable sample after an invalid event; output remains suppressed until a second consecutive acceptable sample returns the monitor to `GOOD`.

## Simulated Thresholds

| Parameter | Value | Behavior |
|---|---:|---|
| Preferred PPG amplitude | 0.70 | At or above this level is considered acceptable |
| Invalid PPG amplitude | 0.40 | Below this level is considered invalid |
| High-motion threshold | 0.60 | Above this level is considered invalid |
| Recovery confirmation | 2 samples | Two consecutive acceptable samples required after invalid state |

## Example Output

```text
Time: 0 ms    | State: GOOD       | HR output: ALLOWED
Time: 1000 ms | State: DEGRADED   | HR output: ALLOWED
Time: 2000 ms | State: INVALID    | HR output: SUPPRESSED
Time: 3000 ms | State: RECOVERING | HR output: SUPPRESSED
Time: 4000 ms | State: GOOD       | HR output: ALLOWED
```

## Project Structure

```text
wearable-signal-quality-monitor-cpp/
├── include/
│   ├── sensor_sample.hpp
│   └── signal_quality_monitor.hpp
├── src/
│   ├── main.cpp
│   └── signal_quality_monitor.cpp
├── data/
│   └── signal_quality_event_log.csv
├── tests/
├── docs/
├── wearable-signal-quality-monitor-cpp.sln
├── wearable-signal-quality-monitor-cpp.vcxproj
└── README.md
```

## Build and Run

### Visual Studio

1. Open `wearable-signal-quality-monitor-cpp.sln`.
2. Select the `Debug` and `x64` configuration.
3. Run with `Ctrl + F5`.

The program writes a simulated event log to:

```text
data/signal_quality_event_log.csv
```

## Skills Demonstrated

- C++17
- Object-oriented design
- Finite-state-machine logic
- Sensor-data structures
- Source/header separation
- Safe output-suppression logic
- Consecutive-sample recovery confirmation
- CSV event logging with `std::ofstream`
- Visual Studio build workflow
- Git/GitHub-ready project organization

## Limitations

This is an educational simulation only. It does not use real physiological data, validated signal processing, medical-device software controls, real-time embedded hardware, clinical testing, or formal verification.