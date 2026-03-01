#ifndef NOTES_H
#define NOTES_H

#include <stdint.h>
#include <esp32-hal-ledc.h>

struct Duration
{
  uint8_t numerator;
  uint8_t denominator;
};

constexpr Duration WHOLE     = {1,1};
constexpr Duration HALF      = {1,2};
constexpr Duration QUARTER   = {1,4};
constexpr Duration EIGHT     = {1,8};
constexpr Duration SIXTEENTH = {1,16};


#define NOTE_REST NOTE_MAX

struct Note
{
  note_t note;
  uint8_t octave;
  Duration duration;
};

#endif  // NOTES_H
