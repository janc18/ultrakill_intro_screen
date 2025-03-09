#ifndef MANAGEAUDIO_H
#define MANAGEAUDIO_H

void GenerateKeyClickSound(short *buffer, int samples, float baseFrequency, int sampleRate);

void GenerateLaserShot(short *buffer, int samples, float frequency, int sampleRate);
void simpleSound(short* buffer, int samples, float frequency, int sampleRate);
void GenerateGameOverSound(short *buffer, int samples, float frequency, int sampleRate);
#endif // !MANAGEAUDIO_H

