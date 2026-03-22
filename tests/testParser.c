#include <stdio.h>
#include "jsonParser/parser.h"
char json[]="{\"intro\":[{\"text\":\"TEST1\",\"effect\":\"EFFECT1\",\"time\":5.2,\"skip\":false,\"xPos\":156,\"yPos\":75,\"sizeFont\":56,\"color\":\"BLUE\"},{\"text\":\"TEST2\",\"effect\":\"EFFECT2\",\"time\":5,\"skip\":true,\"xPos\":120,\"yPos\":45,\"sizeFont\":56,\"color\":\"RED\"}]}";
int main(){
    phrase_t Phrases[10];
    int PhrasesDetected=0;
    int status=getPhrases(json,Phrases,&PhrasesDetected,10);
    if (status!=0){
        return 0;
    }
    for (int i=0; i< PhrasesDetected;i++){
        printf("Phrase %s\nEffect %s\nSkip %d\nTime %f\nxPos %d\nyPos %d\nSize font %d\nColor %s\n",
            Phrases[i].text,
            Phrases[i].effect,
            Phrases[i].skip,
            Phrases[i].time,
            Phrases[i].x,
            Phrases[i].y,
            Phrases[i].sizeFont,
            Phrases[i].color
        );
    }
}