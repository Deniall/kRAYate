#include "Audio.h"

Audio::init(){

}


/*
*plays sound chunk on a specific channel a number of times
* chunk - the chunk object to be played
* channel - the channel the sound is played on
* loops - the number of times the chunk is looped
*/
void Audio::playSound(Mix_Chunk chunk, int channel, int loops){
    Mix_PlayChannel(-1, chunk, loops);
}

void Audio::playSound(Mix_Chunk chunk){

}

void Audio::playSound(Mix_Chunk chunk, int x, int y){

}

void Audio::playSound(String path){

}


void Audio::void playSound(String path, int x, int y){

}

/*
* Creates a sound chunk based on the file stored at the file path
* path - the path where the audio is stored
*/
Mix_Chunk Audio::getChunk(String path){
    return Mix_LoadWaAV(path);
}
