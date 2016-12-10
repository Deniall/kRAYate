#ifndef AUDIO_H
#define AUDIO_H

#include "SDL_mixer.h"


class Audio
{
    public:
        bool init();
        void playSound(Mix_Chunk chunk, int channel, int loops);
        void playSound(Mix_Chunk chunk);
        void playSound(Mix_Chunk chunk, int x, int y);
        void playSound(String path);
        void playSound(String path, int x, int y);
        Mix_Chunk getChunk(String path);

    protected:

    private:
};

#endif // AUDIO_H
