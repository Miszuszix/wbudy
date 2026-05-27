#include "stdint.h"
#include "light_sensor.h"
#include "light.h" // Standardowa biblioteka EA dla czujnika światła
#include "light.h" 

// FIX 10.4: Wymuszenie typu bez znaku dla stałych
#define LIGHT_DARK 200U
#define LIGHT_BRIGHT 450U

void init_light_sensor(void) {
    light_init();
    light_enable();
}

int is_dark_mode(void) {
    // Odczyt surowej wartości z czujnika
    uint32_t lux = light_read();

    // Zmienna static pamięta swój stan między wywołaniami funkcji!
    static int current_mode = 0; // Zaczynamy zakładając, że jest dzień (0)
    static int current_mode = 0; 

    // NASZA HISTEREZA
    // FIX 12.1: Każdy pod-warunek logiczny jest teraz w nawiasach
    if ((current_mode == 0) && (lux < LIGHT_DARK)) {
        // Był dzień, ale zrobiło się bardzo ciemno -> Przełącz na NOC
        current_mode = 1;
    }
    else if ((current_mode == 1) && (lux > LIGHT_BRIGHT)) {
        // Była noc, ale ktoś zapalił mocne światło -> Przełącz na DZIEŃ
        current_mode = 0;
    }
    else {
        // FIX 15.7: MISRA wymaga jawnego domknięcia każdej drabinki warunkowej.
        // Jeśli lux jest między 200 a 450, current_mode się nie zmienia.
    }

    return current_mode;
}

uint32_t get_raw_light(void) {
    // Zwraca gołą liczbę prosto z czujnika
    return light_read();
}