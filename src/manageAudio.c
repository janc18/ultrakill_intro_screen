#include "manageAudio.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

void GenerateKeyClickSound(short* buffer, int samples, float baseFrequency, int sampleRate)
{
    float randomPitch = (rand() % 20 - 10) / 100.0f; 
    float frequency   = baseFrequency * (1.0f + randomPitch);

    for (int i = 0; i < samples; i++)
    {
        float t     = (float)i / sampleRate;
        float value = (fmod(t * frequency, 1.0) < 0.5) ? 1.0f : -1.0f; 
            float decay = 1.0f - (float)i / samples;
        buffer[i]   = (short)(value * 32000 * decay);
    }
}

void GenerateLaserShot(short* buffer, int samples, float frequency, int sampleRate)
{
    for (int i = 0; i < samples; i++)
    {
        float t          = (float)i / sampleRate;
        float pitchDecay = 1.0f - (float)i / samples; 
        float value      = (fmod(t * frequency * pitchDecay, 1.0) < 0.5) ? 1.0f : -1.0f;
        buffer[i]        = (short)(value * 32000);
    }
}
void GenerateGameOverSound(short* buffer, int samples, float frequency, int sampleRate)
{
    for (int i = 0; i < samples; i++)
    {
        float t          = (float)i / sampleRate;
        float pitchDecay = 1.0f - (float)i / samples;
        float value      = 2.0f * fabs(2.0f * fmod(t * frequency * pitchDecay, 1.0) - 1.0) - 1.0;
        buffer[i]        = (short)(value * 32000);
    }
}

void simpleSound(short* buffer, int samples, float frequency, int sampleRate)
{
    for (int i = 0; i <samples; i++)
    {
        float t = (float)i /sampleRate;                           
        buffer[i] = (short)(sinf(2.0f * PI * frequency* t) * 32000);
    }
}
