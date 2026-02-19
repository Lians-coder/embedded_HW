#ifndef TIMES_H
#define TIMES_H

// periods of states
constexpr uint32_t STABLE_GREEN_P  = 7000;
constexpr uint32_t BLINK_GREEN_P   = 1500;
constexpr uint32_t STABLE_YELLOW_P = 1500;
constexpr uint32_t STABLE_RED_P    = 2000;
constexpr uint32_t BEFORE_GREEN_P  = 1500;
constexpr uint32_t SPECIAL_P       = 0;  // infinity

// periods of blinking
constexpr uint32_t BLINK_T = 200;
constexpr uint32_t ERROR_T = 50;

#endif  // TIMES_H
