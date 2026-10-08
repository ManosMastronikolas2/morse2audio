#include "morse2audio.h"
#include <stdio.h>
#include <stdlib.h>

FILE* f;
ma_engine eng;
ma_waveform_config beepConfig;
ma_waveform beepWave;
ma_sound beepSound;

int openFile(char* fname){
    f = fopen(fname,"r");
    if(!f) return 1;
    return 0;
}

int openEngine(){
    if (ma_engine_init(NULL, &eng) != MA_SUCCESS) {
        return -1;
    }

    ma_waveform_config beepConfig = ma_waveform_config_init(
        ma_format_f32,         // Audio format
        2,                     // Channels (Stereo)
        48000,                 // Sample rate
        ma_waveform_type_sine, // Wave type (sine = smooth beep, square = harsh retro beep)
        0.2,                   // Amplitude / Volume (0.0 to 1.0)
        400.0                  // Frequency in Hz
    );

    ma_waveform_init(&beepConfig, &beepWave);

    
    return 0;
}

void playBeep(char c){

    ma_sound beepSound;
    ma_sound_init_from_data_source(&eng, &beepWave, 0, NULL, &beepSound);

    ma_uint64 currTime = ma_engine_get_time(&eng);

    ma_uint64 frames;
    
    frames = 0;
    if(c=='.') frames = 24000;
    else if(c=='-') frames = 48000;

    ma_sound_set_stop_time_in_pcm_frames(&beepSound, currTime + frames);
    ma_sound_start(&beepSound);

    ma_sound_uninit(&beepSound);

}

void playFile(){
    char c;
    while((c = fgetc(f)) != EOF){
        printf("%c",c);
        if(c!='-' && c!='.'){
            printf("Invalid character!\n");
        }else{
            playBeep(c);
        }
    }
    ma_waveform_uninit(&beepWave);
    ma_engine_uninit(&eng);
}