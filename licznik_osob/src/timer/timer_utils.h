#ifndef TIMER_UTILS_H
#define TIMER_UTILS_H

#include <stdint.h>

/**
 * @brief Pobiera globalny czas pracy systemu.
 *
 * Funkcja opiera się na sprzętowym przerwaniu SysTick_Handler, 
 * które jest wywoływane automatycznie przez rdzeń ARM co 1 milisekundę.
 * * @return Czas w milisekundach (ticks) od momentu startu mikrokontrolera.
 */
uint32_t getTicks(void);

#endif