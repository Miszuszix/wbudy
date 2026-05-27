#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

/**
 * @brief Inicjalizuje moduł audio oraz przetwornik cyfrowo-analogowy (DAC).
 *
 * Konfiguruje odpowiednie piny mikrokontrolera (P0.26) do obsługi wyjścia 
 * analogowego oraz uruchamia sprzętowy układ DAC do generowania dźwięku.
 */
void init_audio(void);

/**
 * @brief Odtwarza zdefiniowaną melodię na wbudowanym głośniku.
 *
 * @param songIndex Indeks melodii do odtworzenia. Obsługiwane wartości:
 * - 0: Dźwięk wejścia
 * - 1: Dźwięk wyjścia
 * - 2: Alarm przepełnienia
 */
void playSong(int songIndex);

#endif