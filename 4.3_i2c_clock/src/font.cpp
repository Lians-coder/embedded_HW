#include "font.hpp"


const uint8_t* getLetter(char c)
{
  for (int i = 0; i < sizeof(Font::letterIndex) - 1; i++)
  {
    if (Font::letterIndex[i] == c)
    {
      return Font::letters[i];
    }
  }
  return nullptr;
}


const uint8_t* getGlyph(char c)
{
  if (c >= '0' && c <= '9')
  {
    return Font::digits[c - '0'];
  }
  
  if (c >= 'A' && c <= 'Z')
  {
    return getLetter(c);
  }

  switch(c)
  {
    case ' ' :
      return Font::SPACE;
    case '.' :
      return Font::DOT;
    case 'd' :
      return Font::DEGREE;
    case ':' :
      return Font::COLON;
    case '+' :
      return Font::PLUS;
    case '-' :
      return Font::MINUS;
  }

  return nullptr;
}
