#include "timer_utils.h"

void SysTick_Handler(void);

static volatile uint32_t msTicks = 0U;

// To przerwanie sprzętowe działa w tle
void SysTick_Handler(void) {
    msTicks++;
}

// Funkcja do odczytu czasu
uint32_t getTicks(void) {
    return msTicks;
}