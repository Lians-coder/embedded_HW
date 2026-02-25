# 2.6. Debounce

## Schematic

KiCad schematics were as for HW 2.4:

- for simple [pull-up button](https://github.com/Lians-coder/embedded_HW/blob/main/2.4_debounce/without_rc.kicad_sch);
- for one with [RC filter](https://github.com/Lians-coder/embedded_HW/blob/main/2.4_debounce/with_rc.kicad_sch).  

## Code for each part

> All *src* files were rewritten using **ESP-IDF** platform.  

### Part 1

[Without debounce](https://github.com/Lians-coder/embedded_HW/blob/main/2.6_debounce_esp-idf/1_without_db.cpp):  

- interrupt on FALLING,
- counter increments in ISR,
- counter printed to log.  

### Part 2

**Software debounce** through [timer](https://github.com/Lians-coder/embedded_HW/blob/main/2.6_debounce_esp-idf/2_timer_db.cpp):  

- ignores interrupt if < 50 ms has passed since the previous one,
- implemented outside an ISR.  

### Part 3

[State-based](https://github.com/Lians-coder/embedded_HW/blob/main/2.6_debounce_esp-idf/3_state_db.cpp) **software debounce**:  

- interrupt only signals about *event*,
- in `loop()`: *event* accepted only if button is still pressed,
- ignores events on release.  

### Part 4

[Polling and debounce](https://github.com/Lians-coder/embedded_HW/blob/main/2.6_debounce_esp-idf/4_polling_db_without_isr.cpp):  

- without interrupts,
- poll button every 5 ms,
- debounce implemented as a **state machine**.
