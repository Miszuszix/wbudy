#include "rtc_clock.h"

void init_rtc(void) {
    // Inicjalizacja sprzętowego zegara czasu rzeczywistego
    RTC_Init(LPC_RTC);
    RTC_ResetClockTickCounter(LPC_RTC);
    RTC_Cmd(LPC_RTC, ENABLE); // START!

    // Ustawiamy sztywną datę startową (np. start Waszych zajęć)
    RTC_TIME_Type time;
    time.SEC = 0;
    time.MIN = 0;
    time.HOUR = 12;     // 12:00:00

    // Wrzucamy ten czas do sprzętu
    RTC_SetFullTime(LPC_RTC, &time);
}

void get_current_time(RTC_TIME_Type *time) {
    // Odczyt z rejestrów sprzętowych mikrokontrolera do zmiennej
    RTC_GetFullTime(LPC_RTC, time);
}
