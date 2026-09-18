# Known inconsistencies

Reviewed on 2026-09-18. These notes record differences found by reading the repository; no runtime or hardware validation was performed. Existing code and instructions are preserved.

## Two PWM implementations with different completeness

The standalone [PWMController.py](../manipulatorController/manipulatorController/PWMController.py) uses unqualified names such as `armServoPin`, `armOut` and `setPWM` where instance attributes/methods would be expected. It should not be assumed to be a finished reusable driver.

[manual_control_subscriber.py](../manipulatorController/manipulatorController/manual_control_subscriber.py) contains a separate PWMController implementation. Its later updates convert pulse widths to duty-cycle percentages, but its initial `PWM.start(...)` calls pass values in the pulse-width range (such as 700) directly. That initialization needs review against the GPIO PWM API before hardware use.

The documentation update does not change either implementation or any pin/limit settings.
