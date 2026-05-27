#ifndef RTC_CLOCK_H
#define RTC_CLOCK_H

#include "lpc17xx_rtc.h"

// Inicjalizuje sprzętowy zegar (uruchamia tykanie)
void init_rtc(void);

// Wyciąga aktualny czas z układu i zapisuje go do struktury
void get_current_time(RTC_TIME_Type *time);

#endif
