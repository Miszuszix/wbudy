#include <stdint.h>
#include "led_bar.h"
#include "pca9532.h"        // Biblioteka od Embedded Artists dla tego układu
#include "lpc17xx_i2c.h"    // Biblioteka magistrali I2C
#include "lpc17xx_pinsel.h" // Biblioteka do konfigurowania pinów

void init_led_bar(void) {
    // 1. Konfiguracja pinów mikrokontrolera dla I2C2 (SDA na P0.10, SCL na P0.11)
    PINSEL_CFG_Type PinCfg;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Funcnum = 2; // Funkcja 2 to sprzętowe I2C

    PinCfg.Portnum = 0;
    PinCfg.Pinnum = 10;
    PINSEL_ConfigPin(&PinCfg);
    PinCfg.Pinnum = 11;
    PINSEL_ConfigPin(&PinCfg);

    // 2. Uruchomienie magistrali I2C z prędkością 100 kHz
    I2C_Init(LPC_I2C2, 100000);
    I2C_Cmd(LPC_I2C2, ENABLE);

    // 3. Inicjalizacja samego układu PCA9532
    pca9532_init();
}

void update_led_bar(int liczba_osob) {
    uint16_t maska_zapalona = 0;

    // Zabezpieczenie: mamy tylko 16 diod, więc nie możemy zapalić więcej
    if (liczba_osob > 16) {
        liczba_osob = 16;
    }

    // Trik z przesunięciem bitowym
    if (liczba_osob == 16) {
        maska_zapalona = 0xFFFF; // Zapal wszystkie 16 diod
    }
    else if (liczba_osob > 0) {
        // Np. dla 3 osób: (1 << 3) to binarnie 1000 (dziesiętnie 8).
        // 8 - 1 to 7, co binarnie daje 0111 (3 jedynki = 3 diody!)
        maska_zapalona = (1 << liczba_osob) - 1;
    }

    // Funkcja pca9532_setLeds przyjmuje dwa parametry:
    // 1. maska diod do ZAPALENIA
    // 2. maska diod do ZGASZENIA (używamy ~ czyli odwrotności maski zapalonej)
    pca9532_setLeds(maska_zapalona, ~maska_zapalona);
}
