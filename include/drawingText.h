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
  int sizeText;
  Color color;
  int numberOfStringDrawed;
  Sound sound;
} stringData_t;

int getRemainingChars(const char *text, int currentFPS, int currentFrameCounter,
                      int *currentStringIndex, int *lastIndex);
int drawAllStrings(stringData_t *stringData);
int drawSecuenceOfStrings(stringData_t *stringData, Color color, int sizeText);
bool checkIfCharacterIs(const char *string,char character,int indexString);
int configStringData(stringData_t* stringData, int xPos, int yPos, Color color, int sizeText);
#endif
