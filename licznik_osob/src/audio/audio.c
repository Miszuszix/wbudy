#include "audio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_dac.h"    // Biblioteka obsługująca sprzętowy DAC
#include "lpc17xx_pinsel.h" // Biblioteka do zmiany funkcji pinów

void init_audio(void) {
    PINSEL_CFG_Type PinCfg;

    // Zamiast zwykłego GPIO, przypisujemy pinowi funkcję nr 2, czyli AOUT (Analog Out)
    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Portnum = 0;
    PinCfg.Pinnum = 26; // Pin P0.26, do którego fizycznie podpięty jest głośnik
    PINSEL_ConfigPin(&PinCfg);

    // Uruchomienie sprzętowego układu DAC
    DAC_Init(LPC_DAC);
}

// Wewnętrzna funkcja do grania pojedynczego dźwięku
// UWAGA: Zakładam, że korzystasz z jakiejś funkcji opóźniającej (delay).
// Często studenci piszą własną pętlę for lub używają Timer0.
static void playNote(uint32_t period, uint32_t duration_ms) {
    uint32_t elapsed = 0;
    uint32_t half_period = period / 2U;
    uint32_t duration_us = duration_ms * 1000U;

    while (elapsed < duration_us) {
        // DAC przyjmuje wartości od 0 do 1023.
        // 1023 to maksymalne napięcie na membranie głośnika.
        DAC_UpdateValue(LPC_DAC, 1023U);

        // Zastąp to swoją funkcją opóźnienia, np. delay_us(half_period)
        Timer0_Wait(1);

        // 0 to brak napięcia (membrana opada)
        DAC_UpdateValue(LPC_DAC, 0U);

        // Zastąp to swoją funkcją opóźnienia, np. delay_us(half_period)
        Timer0_Wait(1);

        elapsed += period;
    }
}

void playSong(int songIndex) {
    if (songIndex == 0) {
        // Dźwięk wejścia (rosnący)
        playNote(1912, 100);
        playNote(1517, 150);
    }
    else if (songIndex == 1) {
        // Dźwięk wyjścia (opadający)
        playNote(1517, 100);
        playNote(1912, 150);
    }
    else if (songIndex == 2) {
        // Dźwięk błędu/limitu (niski i długi)
        playNote(2551, 300);
        playNote(2551, 300);
    }
    else {
        
    }
}
