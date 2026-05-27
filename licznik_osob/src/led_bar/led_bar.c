#include <stdint.h>
#include "led_bar.h"
#include "pca9532.h"        
#include "lpc17xx_i2c.h"    
#include "lpc17xx_pinsel.h" 

void init_led_bar(void) {
    PINSEL_CFG_Type PinCfg;
    
    // Zabezpieczenie typów (wymuszenie formatu Unsigned)
    PinCfg.OpenDrain = 0U;
    PinCfg.Pinmode = 0U;
    PinCfg.Funcnum = 2U; 
    PinCfg.Portnum = 0U;
    PinCfg.Pinnum = 10U;
    PINSEL_ConfigPin(&PinCfg);
    
    PinCfg.Pinnum = 11U;
    PINSEL_ConfigPin(&PinCfg);

    // Inicjalizacja
    I2C_Init(LPC_I2C2, 100000U);
    I2C_Cmd(LPC_I2C2, ENABLE);
    pca9532_init();
}

void update_led_bar(int liczba_osob) {
    uint16_t maska_zapalona = 0U;
    
    // FIX 17.8: Tworzymy kopię i od razu rzutujemy na unsigned
    uint32_t lokalna_liczba = (uint32_t)liczba_osob;

    if (lokalna_liczba > 16U) {
        lokalna_liczba = 16U;
    }

    if (lokalna_liczba == 16U) {
        maska_zapalona = 0xFFFFU; // FIX 10.3: dodany sufiks U
        maska_zapalona = 0xFFFFU; 
    }
    else if (lokalna_liczba > 0U) {
        // FIX 10.1 i 10.3: 1U wymusza bezpieczne przesunięcie bitowe.
        // Jawne rzutowanie (uint16_t) na samym początku ucina 32-bitowy wynik do 16 bitów.
        maska_zapalona = (uint16_t)((1U << lokalna_liczba) - 1U);
    }
    else {
        // FIX 15.7: Zabezpieczenie przed brakiem domknięcia
    }

    // FIX 10.1: Odwrotność bitowa (~) podbija typ do signed int 32-bit.
    // Musimy rzutować ten wynik z powrotem do uint16_t przed wysłaniem.
    pca9532_setLeds(maska_zapalona, (uint16_t)(~maska_zapalona));
}