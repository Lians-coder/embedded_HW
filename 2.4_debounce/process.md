# Hardware Interrupts

## Schematic

KiCad schematics for simple [pull-up button](https://github.com/Lians-coder/embedded_HW/blob/main/2.4_debounce/without_rc.kicad_sch) and for one with [RC filter](https://github.com/Lians-coder/embedded_HW/blob/main/2.4_debounce/with_rc.kicad_sch).  

## Code for each part

### Part 1

[Without debounce](https://github.com/Lians-coder/embedded_HW/blob/main/2.4_debounce/1_without_db.cpp):  

- interrupt on FALLING,
- counter increments in ISR,
- counter printed to log.  

### Part 2

**Software debounce** through [timer](https://github.com/Lians-coder/embedded_HW/blob/main/2.4_debounce/2_timer_db.cpp):  

- ignores interrupt if < 50 ms has passed since the previous one,
- implemented outside an ISR.  

### Part 3

[State-based](https://github.com/Lians-coder/embedded_HW/blob/main/2.4_debounce/3_state_db.cpp) **software debounce**:  

- interrupt only signals about *event*,
- in `loop()`: *event* accepted only if button is still pressed,
- ignores events on release.  

### Part 4

[Polling and debounce](https://github.com/Lians-coder/embedded_HW/blob/main/2.4_debounce/4_polling_db_without_isr.cpp):  

- without interrupts,
- poll button every 5 ms,
- debounce implemented as a **state machine**.

## Process

The series of 50 presses each were performed with variable press speeds and contact force for each of parts, without and with a RC filter.  

## Results

### Without RC filter

| Part | Method | Number of false positives | Delay | Difficulty |
| -- | -- | -- | -- | -- |
| 1 | without debounce | 6 | no | Easy |
| 2 | timer-based | 2 | no | Medium |
| 3 | state-based | 2 | no | Easy |
| 4 | polling and debounce | 0 | no | Hard |

## With RC filter

[//] The circuit with current realization of *RC low-pass filter* somehow works worse, then without it.  

| Part | Method | Number of false positives | Delay | Difficulty |
| -- | -- | -- | -- | -- |
| 1 | without debounce | 46 | no | Easy |
| 2 | timer-based | 50 | no | Medium |
| 3 | state-based | 5 | no | Easy |
| 4 | polling and debounce | 0 | no | Hard |
