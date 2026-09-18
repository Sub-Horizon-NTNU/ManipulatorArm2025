# ManipulatorArm2025

## What this repository is for

ROS 2 prototype for **keyboard control of a manipulator arm**, with C++ input/control nodes and a Raspberry Pi Python GPIO output node.

## Data flow

1. [keyLogger](keyLogger/) reads terminal key presses and publishes `keyPresses` (`std_msgs/String`).
2. [manualController](manualController/) converts keys into `manualControlAngle` (`std_msgs/Float64`) and `manualControlSpeed` (`std_msgs/Int32`).
3. [manipulatorController](manipulatorController/) subscribes to those values and drives arm/wrist PWM on the Raspberry Pi.

See [ManualControllerNode.hpp](manualController/include/ManualControllerNode.hpp) for the ROS interfaces and [manual_control_subscriber.py](manipulatorController/manipulatorController/manual_control_subscriber.py) for the GPIO implementation. That implementation uses BCM pins 17, 22 and 27 for arm, wrist and light outputs.

## Development status

The repository contains implementation code, but no complete hardware setup or verified operating procedure. Implementation discrepancies are recorded separately in [docs/INCONSISTENCIES.md](docs/INCONSISTENCIES.md).

Treat this as a hardware prototype requiring review of GPIO wiring, PWM units and limits before operation. It requires ROS 2 C++/Python support and `RPi.GPIO` on a compatible Raspberry Pi. The source layout contains three ROS packages; build them in a ROS 2 workspace after installing their dependencies.
