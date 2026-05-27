#ifndef RTC_CLOCK_H
#define RTC_CLOCK_H

#include "lpc17xx_rtc.h"

/**
 * @brief Inicjalizuje sprzętowy zegar czasu rzeczywistego.
 *
 * Uruchamia wewnętrzne taktowanie modułu RTC mikrokontrolera i ustawia
 * sztywno zdefiniowany w kodzie czas początkowy (godzina 12:00:00)
 * jako punkt startowy systemu.
 */
void init_rtc(void);

/**
 * @brief Pobiera aktualny czas z rejestrów sprzętowych RTC.
 *
 * @param time Wskaźnik na strukturę RTC_TIME_Type, do której zostaną
 * skopiowane aktualne dane o sekundach, minutach, godzinach.
 */
void get_current_time(RTC_TIME_Type *time);

#endif