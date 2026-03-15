#if !defined(PARSER)
#define PARSER
#include <stdbool.h>

typedef struct phrase_t
{
    char text[255];
    char effect[50];
    float time;
    bool skip;
    int xPos;
    int yPos;
}phrase_t;

enum EFFECT{
    ERROR=-1,
    NO_EFFECT=0,
    RED,
    BLUR
};

int testingHowWorks(char* string);
int getPhrases(char* string,phrase_t *Phrases, int *numberOfPhrasesDetected, int NumberOfPhrasesSuported);

#endif // PARSER
