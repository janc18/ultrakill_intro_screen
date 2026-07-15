#include "textScheduler/scheduler.h"
#include <stdio.h>
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
    DispatchTerminalMessageV1(dispatcher,Phrase,index);
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
    DispatchTerminalMessageV1(dispatcher,Phrase,i);
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

void DrawPhrases(terminalMessages_t* d, phrase_t* Phrase)
{
    for (int i = 0; i < d->currentIndex; i++)
    {
        int indexDisplacement=i-1;
        if (Phrase[indexDisplacement].stayInScreen && d->drew[indexDisplacement])
        {
            DrawTextV1Terminal(Phrase,indexDisplacement);
            d->drew[indexDisplacement]=false;
        }
    }
}

void DrawTextV1Terminal(phrase_t *Phrase,int indexDisplacement){
    DrawText(Phrase[indexDisplacement].text,
        Phrase[indexDisplacement].x,
        Phrase[indexDisplacement].y,
        Phrase[indexDisplacement].sizeFont,
        processColor(Phrase->color));
}
void DispatchTerminalMessageV1(terminalMessages_t* dispatcher,phrase_t* Phrase, int index){
            dispatchTerminalMessage(dispatcher,
            Phrase[index].text,
            Phrase[index].x,
            Phrase[index].y,
            Phrase[index].sizeFont,
            Phrase[index].time,
            Phrase[index].skip,
            Phrase[index].effect,
            Phrase->color);
}