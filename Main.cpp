#include "Game.h"

//  For sound
void initSDL();
void quitSDL();

int main(int argv, char *argc[])
{
    initSDL();
    MainGame();
    quitSDL();
    return 0;
}   

void initSDL()
{
    SDL_Init (SDL_INIT_AUDIO);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
}
void quitSDL()
{
    Mix_FreeChunk(g_chunk);
    Mix_Quit();
    SDL_Quit();
}