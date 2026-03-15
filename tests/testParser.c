#include <stdio.h>
#include "jsonParser/parser.h"
char json[]="{\"intro\":[{\"text\":\"TEST1\",\"effect\":\"EFFECT1\",\"time\":5.2,\"skip\":false,\"xPos\":156,\"yPos\":75},{\"text\":\"TEST2\",\"effect\":\"EFFECT2\",\"time\":5,\"skip\":true,\"xPos\":120,\"yPos\":45}]}";
int main(){
    phrase_t Phrases[10];
    int PhrasesDetected=0;
    int effect=getPhrases(json,Phrases,&PhrasesDetected,10);
    for (int i=0; i< PhrasesDetected;i++){
        printf("Phrase %s\nEffect %s\nSkip %d\nTime %.2f\nxPos %d\nyPos %d\n",
            Phrases[i].text,
            Phrases[i].effect,
            Phrases[i].skip,
            Phrases[i].time,
            Phrases[i].xPos,
            Phrases[i].yPos
        );
    }
}