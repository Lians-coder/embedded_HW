#ifndef MELODIES_H
#define MELODIES_H

#include "notes.h"

struct Melody
{
  const Note* notes;
  uint16_t size;
  uint16_t bmp;
  bool loop;
};

// NOTE_C, NOTE_Cs, NOTE_D, NOTE_Eb, NOTE_E, NOTE_F, NOTE_Fs, NOTE_G, NOTE_Gs, NOTE_A, NOTE_Bb, NOTE_B, NOTE_MAX

constexpr Note nStarTrekDS9[] = 
{
  {NOTE_G, 4, SIXTEENTH},
  {NOTE_C, 5, SIXTEENTH},
  {NOTE_E, 5, SIXTEENTH},
  {NOTE_D, 5, HALF},
  {NOTE_F, 5, EIGHT},
  {NOTE_E, 5, SIXTEENTH},
  {NOTE_F, 5, SIXTEENTH},
  {NOTE_G, 5, HALF},
  {NOTE_C, 5, EIGHT},
  {NOTE_C, 6, EIGHT},
  {NOTE_B, 5, SIXTEENTH},
  {NOTE_G, 5, SIXTEENTH},
  {NOTE_C, 5, EIGHT},
  {NOTE_D, 5, HALF},
  {NOTE_F, 4, QUARTER},
  {NOTE_F, 4, EIGHT},
  {NOTE_G, 4, QUARTER},
  {NOTE_G, 4, EIGHT},
  {NOTE_C, 5, SIXTEENTH},
  {NOTE_C, 6, HALF},
  {NOTE_REST, 0, WHOLE}
};

constexpr Melody StarTrekDS9 = 
{
  nStarTrekDS9,
  sizeof(nStarTrekDS9)/sizeof(Note),
  72,
  true  
};


constexpr Note nStarTrekVoyager[] =
{
  {NOTE_Cs, 5, HALF},
  {NOTE_Fs, 4, HALF},
  {NOTE_Fs, 5, HALF},
  {NOTE_F,  5, QUARTER},
  {NOTE_Cs, 5, HALF},
  {NOTE_Eb, 5, HALF},
  {NOTE_Cs, 5, QUARTER},
  {NOTE_Bb, 5, HALF},
  {NOTE_Fs, 5, QUARTER},  
  {NOTE_Fs, 5, EIGHT},
  {NOTE_Eb, 5, EIGHT},
  {NOTE_Cs, 5, EIGHT},
  {NOTE_Fs, 4, EIGHT},
  {NOTE_Fs, 4, HALF},
  {NOTE_REST, 0, EIGHT},
  {NOTE_Cs, 5, EIGHT},
  {NOTE_Gs, 4, EIGHT},
  {NOTE_Cs, 4, QUARTER},
  {NOTE_Cs, 4, HALF},
  {NOTE_Gs, 4, EIGHT},
  {NOTE_Fs, 4, WHOLE},
  {NOTE_REST, 0, WHOLE}
};

constexpr Melody StarTrekVoyager = 
{
  nStarTrekVoyager,
  sizeof(nStarTrekVoyager)/sizeof(Note),
  100,
  true
};


constexpr Note nStarTrekTNG[] =
{
  {NOTE_F,  5, HALF},
  {NOTE_F,  5, EIGHT},
  {NOTE_D,  5, EIGHT},
  {NOTE_Eb, 5, HALF},
  {NOTE_C,  5, EIGHT},
  {NOTE_G,  5, EIGHT},
  {NOTE_F,  5, QUARTER},
  {NOTE_F,  5, EIGHT},
  {NOTE_D,  5, QUARTER},
  {NOTE_D,  5, EIGHT},
  {NOTE_Eb, 5, QUARTER},
  {NOTE_Eb, 5, EIGHT},
  {NOTE_F,  5, EIGHT},
  {NOTE_G,  5, EIGHT},
  {NOTE_Eb, 5, EIGHT},
  {NOTE_F,  5, QUARTER},
  {NOTE_F,  5, EIGHT},
  {NOTE_Eb, 5, QUARTER},
  {NOTE_Eb, 5, EIGHT},
  {NOTE_D,  5, QUARTER},
  {NOTE_D,  5, SIXTEENTH},
  {NOTE_REST, 0, SIXTEENTH},
  {NOTE_D,  5, EIGHT},
  {NOTE_Bb, 4, EIGHT},
  {NOTE_D,  5, EIGHT},
  {NOTE_F,  5, HALF},
  {NOTE_F,  5, QUARTER},
  {NOTE_REST, 0, WHOLE}
};

constexpr Melody StarTrekTNG = 
{
  nStarTrekTNG,
  sizeof(nStarTrekTNG) / sizeof(Note),
  120,
  true
};



constexpr Note nStarWars[] =
{
  {NOTE_G,    4, QUARTER},
  {NOTE_REST, 0, QUARTER},
  {NOTE_G,    4, QUARTER},
  {NOTE_REST, 0, QUARTER},
  {NOTE_G,    4, QUARTER},
  {NOTE_REST, 0, QUARTER},
  {NOTE_Eb,   4, QUARTER},
  {NOTE_REST, 0, EIGHT},
  {NOTE_Bb,   4, EIGHT},
  {NOTE_G,    4, QUARTER},
  {NOTE_REST, 0, QUARTER},
  {NOTE_Eb,   4, QUARTER},
  {NOTE_REST, 0, EIGHT},
  {NOTE_Bb,   4, EIGHT},
  {NOTE_G,    4, HALF},
  {NOTE_REST, 0, HALF},
  {NOTE_D,    5, QUARTER},
  {NOTE_REST, 0, QUARTER},  
  {NOTE_D,    5, QUARTER},
  {NOTE_REST, 0, QUARTER},
  {NOTE_D,    5, QUARTER},
  {NOTE_REST, 0, QUARTER},  
  {NOTE_Eb,   5, QUARTER},
  {NOTE_REST, 0, EIGHT},
  {NOTE_Bb,   4, EIGHT},
  {NOTE_Fs,   4, QUARTER},
  {NOTE_REST, 0, QUARTER},
  {NOTE_Eb,   4, QUARTER},
  {NOTE_REST, 0, EIGHT},
  {NOTE_Bb,   4, EIGHT},
  {NOTE_G,    4, HALF},
  {NOTE_REST, 0, WHOLE}
};

constexpr Melody StarWars = 
{
  nStarWars,
  sizeof(nStarWars) / sizeof(Note),
  225,
  true
};

#endif  // MELODIES_H