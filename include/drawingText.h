#ifndef DRAWING_TEXT_H
#define DRAWING_TEXT_H
#include <raylib.h>
#include <stddef.h>

typedef struct stringData_t {
  const char **strings;
  RenderTexture2D *StringTextures;
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
  int lastTextWidth;
  bool *textureNeedsUpdate;
  Vector2 *texturePosition;
  bool isCharacter;
} stringData_t;

int getRemainingChars(const char *text, int currentFrameCounter,
                      int *currentStringIndex, int *lastIndex);
int drawAllStrings(stringData_t *stringData);
int drawSecuenceOfStrings(stringData_t *stringData);
bool checkIfCharacterIs(const char *string, char character, int indexString);
int configStringData(stringData_t *stringData, int xPos, int yPos, Color color,
                     int sizeText);
int modifyValuesToDrawTheNextString(stringData_t *stringData);
int drawStringsThatHadBeenDrawed(stringData_t *stringData);
int generateStringData(int numberOfStringsToDraw, const char **stringsToDraw,
                       stringData_t *stringData, int xPos, int yPos,
                       Color color, int sizeText, Sound sound);
RenderTexture2D createStringTexture(const char *string,
                                    stringData_t *stringData);
int freeTextureStrings(stringData_t *stringData);
void UpdatePosition(Vector2 *position);
void  UpdateFadeOut(float *alpha,bool *fadingOut);
int fadeOutStringTextures(stringData_t* stringData, float alpha, bool fadingOut);
int triggerEvent(stringData_t *stringData,Texture2D texture1,Texture2D texture2,Rectangle sourceRect,Vector2 position);
int fadeOutTexture(Texture2D texture, float alpha,Rectangle sourceRect,Vector2 position);
#endif
