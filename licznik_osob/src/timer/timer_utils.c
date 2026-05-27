#include "timer_utils.h"

volatile uint32_t msTicks = 0;

// To przerwanie sprzętowe działa w tle
void SysTick_Handler(void) {
    msTicks++;
}

// Funkcja do odczytu czasu
uint32_t getTicks(void) {
    return msTicks;
}
