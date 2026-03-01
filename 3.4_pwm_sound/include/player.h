#ifndef PLAYER_H
#define PLAYER_H

#include "melodies.h"
#include "ledc_pwm.h"

class Player
{
  public:
    void init();
    void start(const Melody& melody, uint32_t now);
    void update(uint32_t now);
    void stop();
    void nextMelody(uint32_t now);

    static const PwmOut outputs[];
    static const Melody* melodies[];
    static const uint8_t melodyCount;

  private:
    void setupTimer();
    void setupChan(uint8_t pin, ledc_channel_t channel);
    void startNote(const Note& note, uint32_t now);
    uint32_t durationToMs(const Duration& duration, uint16_t bmp) const;

    const Melody* currentMelody {nullptr};
    uint32_t noteStartTime {0};
    uint32_t currentDurationMs {0};
    uint16_t currentIndex {0};
    bool playing {false};
    uint8_t pwmChannel;
};

#endif  // PLAYER_H
