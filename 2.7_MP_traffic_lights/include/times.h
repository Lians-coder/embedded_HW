#ifndef TIMES_H
#define TIMES_H

// periods of states
constexpr uint32_t STABLE_GREEN_P  = 7000;
constexpr uint32_t BLINK_GREEN_P   = 2000;
constexpr uint32_t STABLE_YELLOW_P = 2500;
constexpr uint32_t STABLE_RED_P    = 2000;
constexpr uint32_t BEFORE_GREEN_P  = 1000;

// periods of blinking
constexpr uint32_t BLINK_T = 300;
constexpr uint32_t ERROR_T = 100;

#endif  // TIMES_H
