#if !defined(TEXT_SCHEDULER)
#define TEXT_SCHEDULER
#include "terminalEngine/v1View.h"
void scheduleSequentially(terminalMessages_t* dispatcher, phrase_t* Phrase);
void scheduleAllAtTheTime(terminalMessages_t* dispatcher, phrase_t* Phrase);
void scheduleFadeOutAllSkip(terminalMessages_t* dispatcher);
void DrawPhrases(terminalMessages_t* d, phrase_t* Phrase);


#endif // TEXT_SCHEDULER
