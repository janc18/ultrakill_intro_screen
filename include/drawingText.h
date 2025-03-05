#ifndef DRAWING_TEXT_H
#define DRAWING_TEXT_H
#include <raylib.h>
#include <stddef.h>

typedef struct stringData_t {
  const char **strings;
  size_t numberOfStrings;
  int currentIndex;
  int framesCounter;
  int lastindex;
  int xPos;
  int yPos;
  int yPosStart;
  int numberOfStringDrawed;
} stringData_t;

int getRemainingChars(const char *text, int currentFPS, int currentFrameCounter,
                      int *currentStringIndex, int *lastIndex);

int drawSecuenceOfStrings(stringData_t *stringData, Color color, int sizeText);

#endif
