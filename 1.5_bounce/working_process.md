# Bounce

## Schematic

The circuit schematic was designed in KiCad and is available here:  
[KiCad schematic](https://github.com/Lians-coder/embedded_HW/blob/main/1.5_bounce/bounce.kicad_sch).  

Two toggle switch modules were used, each with a 10 kΩ pull-down resistor. In this configuration, pressing a button drives the signal to a HIGH logic level. A logic analyzer was connected to the output line of each toggle switch, while the same signals were simultaneously monitored by the ESP32-S3 via serial output.  

## Counting bounce impulses

> [Code](https://github.com/Lians-coder/embedded_HW/blob/main/1.5_bounce/bounce/main_bounce.cpp) for this part.  

Serial monitor output and logic analyzer traces were collected while experimenting with different button press speeds and contact force. Most of the bounce impulses were observed on the falling edge of the signal. The software counters for both switches did not match the number of physical bounce impulses, with the counters typically registering more events than those observed on the logic analyzer.  

The mean bounce duration for each switch was measured to be up to 39 ms. Based on these observations, a minimum debounce time of 50 ms is required for reliable input processing.  

## Optional debounce

> [Code](https://github.com/Lians-coder/embedded_HW/blob/main/1.5_bounce/debounce/main_debounce.cpp) for this part.  

After introducing debounce logic in the firmware, the serial monitor output became stable and matched the expected number of button presses, while the physical bounce behavior observed on the logic analyzer remained unchanged.  
This confirms that the debounce implementation effectively filtered out transitions caused by mechanical bouncing.  

### Disclaimer

Spurious spikes were observed on the second input when only one button was pressed. This behavior persisted after relocating the wiring on the breadboard.  
