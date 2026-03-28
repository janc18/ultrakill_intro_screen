#include "textScheduler/scheduler.h"

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
                                Phrase[index].skip, Phrase[index].effect);
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
        dispatchTerminalMessage(dispatcher, Phrase[i].text, Phrase[i].x, Phrase[i].y, Phrase[i].sizeFont, Phrase[i].time, Phrase[i].skip,
                                Phrase[i].effect);
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
