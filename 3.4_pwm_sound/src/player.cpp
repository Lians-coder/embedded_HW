#include "player.h"

// to use several channels for polyphonic music later
constexpr PwmOut Player::outputs[] = 
{
  {PIN_BUZZ_1, CH_BUZZ_1}
};


const Melody* Player::melodies[] = {
  &StarTrekDS9,
  &StarTrekVoyager, 
  &StarTrekTNG,
  &StarWars
};

constexpr uint8_t Player::melodyCount = sizeof(Player::melodies) / sizeof(Player::melodies[0]);


void Player::setupTimer()
{
  ledc_timer_config_t timerConfig = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = RESOLUTION,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = FREQ,
    .clk_cfg = LEDC_AUTO_CLK
  };
  ledc_timer_config(&timerConfig);
}


void Player::setupChan(uint8_t pin, ledc_channel_t channel)
{
  ledc_channel_config_t chConfig = {
    .gpio_num = pin,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = channel,
    .timer_sel = LEDC_TIMER_0,
    .duty = DUTY_CYCLE,
    .hpoint = 0
  };

  ledc_channel_config(&chConfig);
}

void Player::init()
{
  setupTimer();

  for (const PwmOut& out : outputs)
  {
    setupChan(out.pin, out.channel);
  }
  pwmChannel = outputs[0].channel;
}


uint32_t Player::durationToMs(const Duration& duration, uint16_t bmp) const
{
  uint32_t wholeNoteAtBmp = 60000UL * 4UL / bmp;
  return (wholeNoteAtBmp * duration.numerator / duration.denominator);
}


void Player::startNote(const Note& note, uint32_t now)
{
  if (note.note == NOTE_REST)
  {
    ledcWriteTone(pwmChannel, 0);
  }
  else
  {
    ledcWriteNote(pwmChannel, note.note, note.octave);
  }
  currentDurationMs = durationToMs(note.duration, currentMelody->bmp);
  noteStartTime = now;
}


void Player::start(const Melody& melody, uint32_t now)
{
  currentMelody = &melody;
  currentIndex = 0;
  playing = true;
  startNote(currentMelody->notes[currentIndex], now);
}


void Player::update(uint32_t now)
{
  if (!playing || !currentMelody)
  {
    return;
  }

  if (now - noteStartTime >= currentDurationMs)
  {
    currentIndex++;

    if (currentIndex >= currentMelody->size)
    {
      if (currentMelody->loop)
      {
        currentIndex = 0;
      }
      else
      {
        stop();
        return;
      }
    }

    startNote(currentMelody->notes[currentIndex], now);
  }
}


void Player::stop()
{
  playing = false;
  ledcWriteTone(pwmChannel, 0);
}


void Player::nextMelody(uint32_t now)
{
  if (!currentMelody)
  {
    return;
  }

  uint8_t idx = 0;
  for (; idx < melodyCount; idx++)
  {
    if (currentMelody == melodies[idx])
    {
      break;
    }
  }

  idx = (idx + 1) % melodyCount;
  start(*melodies[idx], now);
}
