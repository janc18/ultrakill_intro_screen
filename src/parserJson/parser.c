#include "jsonParser/parser.h"
#include "jsonParser/cJSON.h"
#include "stdio.h"
#include "string.h"

int testingHowWorks(char* string)
{
    cJSON* json    = cJSON_Parse(string);
    char*  newjson = cJSON_Print(json);
    printf(newjson);
    return 5;
}

int getPhrases(char* string, phrase_t* Phrases, int* numberOfPhrasesDetected, int NumberOfPhrasesSuported)
{
    // Json Validation
    int    status = -1;
    cJSON* json   = cJSON_Parse(string);
    if (json == NULL)
    {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = ERROR;
        goto end;
    }
    //------

    // Validate scene//
    const cJSON* introData = NULL;
    introData              = cJSON_GetObjectItemCaseSensitive(json, "intro");
    if (!cJSON_IsArray(introData))
    {
        status = ERROR;
        goto end;
    }
    int sizeIntroData = cJSON_GetArraySize(introData);
    if (sizeIntroData == 0)
    {
        status = ERROR;
        goto end;
    }
    else if (sizeIntroData > NumberOfPhrasesSuported)
    {
        status = ERROR;
        goto end;
    }
    *numberOfPhrasesDetected = sizeIntroData;
    //-------------
    const cJSON* phrasesJson = NULL;
    int          iteration   = 0;

    cJSON_ArrayForEach(phrasesJson, introData)
    {
        cJSON* text = cJSON_GetObjectItemCaseSensitive(phrasesJson, "text");
        if (!cJSON_IsString(text)||text==NULL)
        {
            printf("ERROR: text\n");
            status = ERROR;
            goto end;
        }
        cJSON* effect = cJSON_GetObjectItemCaseSensitive(phrasesJson, "effect");
        if (!cJSON_IsString(effect)||effect==NULL)
        {
            status = ERROR;
            printf("ERROR: effect\n");
            goto end;
        }
        cJSON* time = cJSON_GetObjectItemCaseSensitive(phrasesJson, "time");
        if (!cJSON_IsNumber(time)||time==NULL)
        {
            status = ERROR;
            printf("ERROR: time\n");
            goto end;
        }
        cJSON* xPos = cJSON_GetObjectItemCaseSensitive(phrasesJson, "xPos");
        if (!cJSON_IsNumber(time)||xPos==NULL)
        {
            status = ERROR;
            printf("ERROR: xPos\n");
            goto end;
        }
        cJSON* yPos = cJSON_GetObjectItemCaseSensitive(phrasesJson, "yPos");
        if (!cJSON_IsNumber(time)||yPos==NULL)
        {
            status = ERROR;
            printf("ERROR: yPos\n");
            goto end;
        }
        cJSON* sizeFont = cJSON_GetObjectItemCaseSensitive(phrasesJson, "sizeFont");
        if (!cJSON_IsNumber(sizeFont)||sizeFont==NULL)
        {
            status = ERROR;
            printf("ERROR: sizeFont\n");
            goto end;
        }
        cJSON* color = cJSON_GetObjectItemCaseSensitive(phrasesJson, "color");
        if (!cJSON_IsString(color)||color==NULL)
        {
            status = ERROR;
            printf("ERROR: Color\n");
            goto end;
        }
        cJSON* skip = cJSON_GetObjectItemCaseSensitive(phrasesJson, "skip");
        if (!cJSON_IsBool(skip)||skip==NULL)
        {
            printf("ERROR: skip\n");
            status = ERROR;
            goto end;
        }
        strcpy(Phrases[iteration].text, text->valuestring);
        Phrases[iteration].skip     = skip->valueint;
        Phrases[iteration].time     = time->valuedouble;
        Phrases[iteration].x=xPos->valueint;
        Phrases[iteration].y=yPos->valueint;
        Phrases[iteration].sizeFont = sizeFont->valueint;
        strcpy(Phrases[iteration].color, color->valuestring);
        strcpy(Phrases[iteration].effect, effect->valuestring);
        iteration++;
        status = OK;
    }
    goto end;
end:
    cJSON_Delete(json);
    return status;
}
