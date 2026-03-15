#ifndef MANAGEAUDIO_H
#define MANAGEAUDIO_H

#include <raylib.h>
void GenerateKeyClickSound(short *buffer, int samples, float baseFrequency, int sampleRate);
void GenerateLaserShot(short *buffer, int samples, float frequency, int sampleRate);
void simpleSound(short* buffer, int samples, float frequency, int sampleRate);
void GenerateGameOverSound(short *buffer, int samples, float frequency, int sampleRate);
Sound generateSimpleSound(int sampleRate,int samples);
#endif // !MANAGEAUDIO_H

