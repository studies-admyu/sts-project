#include "SoundManager.hpp"

SDL_AudioSpec audioSpec;
int *volumes = new int[NUM_SOUNDS];

struct sample {
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;
} sounds[NUM_SOUNDS];

SoundManager::SoundManager(void)
{
	printf("Initializing sound manager.");
    int status = this->open();
    if(status != 0){
        fprintf(stderr, "Could not start audio! %s", SDL_GetError());
    }
    // set channel 1 to half volume
    Mix_Volume(1, MIX_MAX_VOLUME/2);

    // print the average volume
    fprintf(stdout, "Average volume is %d\n",Mix_Volume(-1,-1));
}

SoundManager::~SoundManager(void)
{
	delete volumes;
    this->close();
}

/*
 * 		mixAudio(void*, Uint8*, int):
 *		Audio mixer so that more than one sound can be played simultaneously
 */
void mixAudio(void *unused, Uint8 *stream, int len)
{
    int i;
    Uint32 amount;
    
    for ( i=0; i<NUM_SOUNDS; ++i ) {
        amount = (sounds[i].dlen-sounds[i].dpos);
        if ( amount > len ) {
            amount = len;
        }
        SDL_MixAudio(stream, &sounds[i].data[sounds[i].dpos], amount, volumes[i]);
        sounds[i].dpos += amount;
    }
}

/*
 * 		open():
 *		Initializes the audioSpec to the desired format and starts the audio
 * 		callback process.
 */

int SoundManager::open(void)
{
    
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return -2;        
    }
    if( Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096 ) == -1 )
    {
        fprintf(stderr, "Mix_OpenAudio: %s\n", Mix_GetError());
        return -3;    
    }
    // load support for the OGG sample/music formats
    int flags=MIX_INIT_OGG;
    int initted=Mix_Init(flags);
    if(initted&flags != flags) 
    {
        fprintf(stderr, "Mix_Init: Failed to init required ogg support!\n");
        fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
        // handle error
    }        
    return 0;
        
}

/*
 * 		close():
 *		Stops the audio callback process, frees memory, and closes the audio device
 */
void SoundManager::close(void)
{
    SDL_PauseAudio(1);
    SDL_CloseAudio();
    for(int i = 0; i < NUM_SOUNDS; i++)
        if(sounds[i].data) SDL_FreeWAV(sounds[i].data);
    memset(sounds, 0, sizeof(sounds));
}

/*
 *		adjustVolume(int, double):
 *		Adjusts the volume of track to the indicated level (percentage).
 *
 *		-track: either SOUNDS or MUSIC
 *		-level: a number between 0 and 1 representing the percentage of
 *				maximum volume
 */
void SoundManager::adjustVolume(int track, double level)
{
	if(level < 0 || level > 1.0){
		printf("SoundManager error. Invalid volume adjustment.\n");
		return;
	}
	if(track != SOUNDS && track != MUSIC){
		printf("SoundManager error. Invalid track.\n");
		return;
	}

	volumes[track] = (int)(level * SDL_MIX_MAXVOLUME);
}

/*
 * 		playSound(std::string):
 *		Plays a sound effect. The sound must be a 16-bit .wav file.
 *
 *		-fileName: String representation of the filename.
 */
void SoundManager::playSound(std::string fileName)
{
    char * file = const_cast<char*>(fileName.c_str());
    Mix_Chunk *sound = NULL;
    fprintf(stdout, "Playing sound: %s\n", file);
    sound = Mix_LoadWAV( file );
    if ( !sound )
    {
        fprintf(stderr, "Mix_LoadWAV: %s\n", Mix_GetError());
        return;
    }
    if( Mix_PlayChannel( -1, sound, 10 ) < 0 )
    {
        fprintf(stderr, "Mix_PlayChannel: %s\n", Mix_GetError());
        return;
    }
//    Mix_FreeChunk( sound );
}

/*
 *		playMusic(std::string):
 *		Plays background music. The music must be a 16-bit .wav file.
 *
 *		-fileName: String representation of the filename.
 */
void SoundManager::playMusic(std::string fileName)
{
	//The music that will be played
    Mix_Music *music = NULL;
    char * file = const_cast<char*>(fileName.c_str());
    music = Mix_LoadMUS( file );
    if( music == NULL )
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file, Mix_GetError());
        return;
    }
    if( Mix_PlayMusic( music, -1 ) == -1 )
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file, Mix_GetError());
        return;
    }
//    Mix_FreeMusic( music );
}