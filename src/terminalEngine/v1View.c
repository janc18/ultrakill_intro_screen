#include "terminalEngine/v1View.h"
#include <stdio.h>
#include <string.h>
int v1View()
{
    return 5;
}
/*
 * Initialize as false the active value in all messages,
 * as define in MAXTERMINALMESSAGES
 */
void terminalDispatcher_Init(terminalMessages_t* d, int PhrasesToDraw)
{
    for (int i = 0; i < MAXTERMINALMESSAGES; i++)
    {
        d->messages[i].active = false;
        d->drew[i]            = false;
    }
    d->PhrasesToDraw = PhrasesToDraw;
    d->currentIndex  = 0;
    printf("frases detectadas %d\n", PhrasesToDraw);
}
/*
 * if current isn't active continue
 * current elapsed accumulate dt.
 * if total elapse is more equal to lifetime make current inactive
 */
void terminalDispatcher_Update(terminalMessages_t* d, float dt)
{
    for (int i = 0; i < MAXTERMINALMESSAGES; i++)
    {
        terminal_t* m = &d->messages[i];

        if (!m->active)
            continue;

        m->elapsed += dt;

        if (!m->skip)
        {
            m->active  = true;
            d->drew[i] = false; // Finish
            continue;
        }

        if (m->elapsed >= m->lifetime)
        {

            m->active  = false;
            d->drew[i] = true; // Finish
        }
    }
}

/*
 * if current isn't active
 * copy all contents to the dispatcher
 */
void dispatchTerminalMessage(terminalMessages_t* d, const char* text, int x, int y, int fontSize, int lifetime, bool skip)
{
    for (int i = 0; i < MAXTERMINALMESSAGES; i++)
    {
        if (!d->messages[i].active)
        {
            terminal_t* m = &d->messages[i];
            strcpy(m->text, text);
            m->x        = x;
            m->y        = y;
            m->fontSize = fontSize;
            m->lifetime = lifetime;
            m->elapsed  = 0.0f;
            m->fadeIn   = 0.2f;
            m->fadeOut  = 0.5f;
            m->active   = true;
            m->skip     = skip;
            return;
        }
    }
}
/*
 * if current not active continue to the next item
 * Define alpha as 1.0f
 * if current elapsed is less than fade in
 *  - alpha is equal to elapsed dived by fade in
 * if current elapsed is more than current lifetime subtract fadeout
 *  - alpha is equal to (lifetime substract elapsed) divided by fadeout
 */
void terminalDispatcher_Draw(terminalMessages_t* d)
{
    for (int i = 0; i < MAXTERMINALMESSAGES; i++)
    {
        terminal_t* m = &d->messages[i];
        if (!m->active)
            continue;

        float alpha = 1.0f;

        if (m->elapsed < m->fadeIn)
        {
            alpha = m->elapsed / m->fadeIn;
        }
        if (m->elapsed > m->lifetime - m->fadeOut)
        {
            if (!m->skip)
            {
                alpha = 1.0f;
            }
            else
            {
                float t = (m->lifetime - m->elapsed) / m->fadeOut;
                alpha   = t;
            }
        }

        Color c = RED;
        c.a     = (unsigned char)(alpha * 255);
        DrawText(m->text, m->x, m->y, m->fontSize, c);
    }
}

// MOVE to another file

void scheduleSequentially(terminalMessages_t* dispatcher, phrase_t* Phrase)
{
    int index = dispatcher->currentIndex;
    if (dispatcher->currentIndex >= dispatcher->PhrasesToDraw)
    {
        return;
    }
    if (dispatcher->messages[0].elapsed >= dispatcher->messages[0].lifetime)
    {
        dispatcher->currentIndex++;
    }

    if (!dispatcher->messages[0].active)
    {
        dispatchTerminalMessage(dispatcher, Phrase[index].text, Phrase[index].x, Phrase[index].y, Phrase[index].sizeFont, Phrase[index].time,
                                Phrase[index].skip);
    }
}

void scheduleAllAtTheTime(terminalMessages_t* dispatcher, phrase_t* Phrase)
{
    if (dispatcher->allDispatched)
    {
        return;
    }
    for (int i = 0; i < dispatcher->PhrasesToDraw; i++)
    {
        dispatchTerminalMessage(dispatcher, Phrase[i].text, Phrase[i].x, Phrase[i].y, Phrase[i].sizeFont, Phrase[i].time, Phrase[i].skip);
    }
    dispatcher->allDispatched = true;
}

void scheduleFadeOutAllSkip(terminalMessages_t* dispatcher)
{
    for (int i = 0; i < dispatcher->PhrasesToDraw; i++)
    {
        terminal_t* message = &dispatcher->messages[i];
        if (!message->skip)
        {
            message->elapsed = message->lifetime - message->fadeOut;
            message->skip    = true;
        }
    }
}