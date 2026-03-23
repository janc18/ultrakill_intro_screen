#ifndef DRAWING_TEXT_H
#define DRAWING_TEXT_H
#include <jsonParser/parser.h>
#include <raylib.h>
#include <stddef.h>
#define MAXTERMINALMESSAGES 50

typedef struct terminal_t
{
    char  text[MAXTEXTCHARACTERS];
    int   x;
    int   y;
    Color color;
    float lifetime;
    float elapsed;
    float fadeIn;
    float fadeOut;
    int   fontSize;
    bool  active;
    bool  skip;
    char effect[40];
} terminal_t;

typedef struct terminalMessages_t
{
    terminal_t messages[MAXTERMINALMESSAGES];
    bool       drew[MAXTERMINALMESSAGES];
    int        currentIndex;
    int        PhrasesToDraw;
    bool       allDispatched;

} terminalMessages_t;

void terminalDispatcher_Init(terminalMessages_t* d, int PhrasesToDraw);
void terminalDispatcher_Update(terminalMessages_t* d, float dt);
void dispatchTerminalMessage(terminalMessages_t* d, const char* text, int x, int y, int fontSize, int lifetime, bool skip,char *effect);
void terminalDispatcher_Draw(terminalMessages_t* d);

// MOVE to another file

void scheduleSequentially(terminalMessages_t* dispatcher, phrase_t* Phrase);
void scheduleAllAtTheTime(terminalMessages_t* dispatcher, phrase_t* Phrase);
void scheduleFadeOutAllSkip(terminalMessages_t* dispatcher);
// MOVE to another file

void drawTextTypeWriter(char* text, int x, int y, int fontSize, Color color, terminal_t* m);


int v1View();

#endif
