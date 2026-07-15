#include <stdio.h>
#include "jsonParser/parser.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    if (argc<2){
        printf("File path not specified, closing\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
        printf("Messages don't found, closing\n");
        exit(1);
    }
    char json[2048];
    int  bytesRead = read(fd, json, sizeof(json));
    phrase_t Phrases[10];
    int PhrasesDetected=0;
    int status=getPhrases(json,Phrases,&PhrasesDetected,10);
    if (status!=0){
        return 0;
    }
    for (int i=0; i< PhrasesDetected;i++){
        printf("Phrase %s\nEffect %s\nSkip %d\nTime %f\nxPos %d\nyPos %d\nSize font %d\nColor %s\nStayinScreen %d\n",
            Phrases[i].text,
            Phrases[i].effect,
            Phrases[i].skip,
            Phrases[i].time,
            Phrases[i].x,
            Phrases[i].y,
            Phrases[i].sizeFont,
            Phrases[i].color,
            Phrases[i].stayInScreen
        );
    }
}