#ifndef AUDIO_H
#define AUDIO_H

// Inicjalizuje pin P0.26 jako wyjście przetwornika analogowego (DAC)
void init_audio(void);

// Odtwarza konkretną melodyjkę (0 - wejście, 1 - wyjście, 2 - alarm limitu)
void playSong(int songIndex);

#endif
