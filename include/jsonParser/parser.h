#if !defined(PARSER)
#define PARSER
#include <stdbool.h>
#include <raylib.h>
#define MAXTEXTCHARACTERS 250
#define MAXEFFECTCHARACTERS 50
#define MAXCOLORCHARACTERS 50
typedef struct phrase_t
{
    char text[MAXTEXTCHARACTERS];
    char effect[MAXEFFECTCHARACTERS];
    float time;
    bool skip;
    int x;
    int y;
    int sizeFont;
    char color[MAXCOLORCHARACTERS];
}phrase_t;

enum STATUS{
    ERROR=-1,
    OK=0
};

int testingHowWorks(char* string);
int getPhrases(char* string,phrase_t *Phrases, int *numberOfPhrasesDetected, int NumberOfPhrasesSuported);

#endif // PARSER
