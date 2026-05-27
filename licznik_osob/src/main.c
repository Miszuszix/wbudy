#include <stdio.h>
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "oled.h"

#include "timer/timer_utils.h"
#include "spi/spi_setup.h"
#include "audio/audio.h"
#include "led_bar/led_bar.h"
#include "light_sensor/light_sensor.h"
#include "eeprom_memory/eeprom_memory.h"
#include "rtc_clock/rtc_clock.h" // NOWY MODUŁ ZEGARA

#define LASER1 6
#define LASER2 8
#define SW3_PORT 0
#define SW3_PIN 4

void check_failed(uint8_t *file, uint32_t line) {
    while(1);
}

int main(void) {
    // --- Inicjalizacja sprzętu ---
    init_ssp();
    oled_init();
    init_audio();
    init_led_bar();
    init_light_sensor();
    init_rtc(); // URUCHOMIENIE ZEGARA

    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }

    // Inicjalizacja pinów dla płyty
    GPIO_SetDir(2, 1<<0, 1);
    GPIO_SetDir(2, 1<<1, 1);
    GPIO_SetDir(0, 1<<27, 1);
    GPIO_SetDir(0, 1<<28, 1);
    GPIO_SetDir(2, 1<<13, 1);

    GPIO_ClearValue(0, 1<<27);
    GPIO_ClearValue(0, 1<<28);
    GPIO_ClearValue(2, 1<<13);

    // Lasery jako WEJŚCIA
    GPIO_SetDir(2, (1<<LASER1), 0);
    GPIO_SetDir(2, (1<<LASER2), 0);

    // Przycisk SW3 jako WEJŚCIE (0)
    GPIO_SetDir(SW3_PORT, (1<<SW3_PIN), 0);

    init_counter_memory();
    int liczba_osob = load_saved_counter();
    int max_osob = 5;

    int stan = 0;
    uint32_t czas_startu = 0;

    // --- ZMIENNE DO NOWEGO SYSTEMU UI ---
    int aktualny_tryb_jasnosci = -1;
    uint32_t bg_color = OLED_COLOR_WHITE;
    uint32_t fg_color = OLED_COLOR_BLACK;

    int tryb_ekranu = 0;           // 0 = Licznik, 1 = Timestamps
    int wymus_odswiezanie = 1;     // Flaga do jednorazowego przerysowania tła
    uint32_t ostatnie_klikniecie = 0; // Do ignorowania drgań przycisku

    // Zmienne do logowania czasu
    RTC_TIME_Type ost_przepelnienie;
    int bylo_przepelnienie = 0;

    char buf_licznik[15];
    char buf_limit[20];
    sprintf(buf_limit, "Limit: %d", max_osob);

    // --- Główna pętla ---
    while(1) {

        // 1. ZMIANA MOTYWU (NOC/DZIEŃ)
        int nowy_tryb_jasnosci = is_dark_mode();
        if (nowy_tryb_jasnosci != aktualny_tryb_jasnosci) {
            aktualny_tryb_jasnosci = nowy_tryb_jasnosci;
            wymus_odswiezanie = 1; // Wymuszamy pełne przerysowanie

            if (aktualny_tryb_jasnosci == 1) { // NOC
                bg_color = OLED_COLOR_BLACK;
                fg_color = OLED_COLOR_WHITE;
            } else {                  // DZIEŃ
                bg_color = OLED_COLOR_WHITE;
                fg_color = OLED_COLOR_BLACK;
            }
        }

        // 2. ODCZYT PRZYCISKU SW3 I ZMIANA TRYBU EKRANU
        // Przyciski zwierają do masy, więc 0 oznacza wciśnięty. Zmieniamy na 1 dla wygody logiki
        int sw3_state = (GPIO_ReadValue(SW3_PORT) & (1 << SW3_PIN)) ? 0 : 1;

        // Jeśli wciśnięto przycisk i minęło 300ms od ostatniego wciśnięcia (żeby nie klikało podwójnie)
        if (sw3_state == 1 && (getTicks() - ostatnie_klikniecie) > 300) {
            ostatnie_klikniecie = getTicks();
            tryb_ekranu = !tryb_ekranu; // Przerzuca 0 na 1, i 1 na 0
            wymus_odswiezanie = 1;      // Nakazujemy całkowite wyczyszczenie ekranu
        }

        // 3. LOGIKA FIZYCZNA (Liczenie osób działa ZAWSZE W TLE!)
        uint32_t port2_state = GPIO_ReadValue(2);
        int laser1 = (port2_state & (1 << LASER1)) ? 1 : 0;
        int laser2 = (port2_state & (1 << LASER2)) ? 1 : 0;

        if (stan == 0) {
            if (laser1 == 1) {
                czas_startu = getTicks();
                stan = 1;
            } else if (laser2 == 1) {
                czas_startu = getTicks();
                stan = 2;
            }
        } else if (stan == 1) {
            if ((getTicks() - czas_startu) > 2000) {
                stan = 0;
            } else if (laser2 == 1) {
                liczba_osob++;
                save_counter(liczba_osob);
                if (liczba_osob > max_osob) {
                    playSong(2); // Głośnik ostrzega NIEZALEŻNIE od ekranu
                    get_current_time(&ost_przepelnienie); // <- ZAPIS TIMESTAMP!
                    bylo_przepelnienie = 1;
                } else {
                    playSong(0);
                }
                stan = 3;
            }
        } else if (stan == 2) {
            if ((getTicks() - czas_startu) > 2000) {
                stan = 0;
            } else if (laser1 == 1) {
                if (liczba_osob > 0) {
                    liczba_osob--;
                    save_counter(liczba_osob);
                    playSong(1);
                }
                stan = 3;
            }
        } else if (stan == 3) {
            if (laser1 == 0 && laser2 == 0) {
                stan = 0;
            }
        }

        update_led_bar(liczba_osob);

        // ==========================================
        // 4. RYSOWANIE INTERFEJSU (UI)
        // ==========================================

        // Krok A: Rysowanie "sztywnych" napisów tylko przy wejściu w nowy tryb
        if (wymus_odswiezanie == 1) {
            oled_clearScreen(bg_color);
            if (tryb_ekranu == 0) {
                oled_putString(1, 1, (uint8_t*)"Licznik Osob:", fg_color, bg_color);
                oled_putString(1, 40, (uint8_t*)buf_limit, fg_color, bg_color);
            } else {
                oled_putString(1, 1, (uint8_t*)"System Czasu:", fg_color, bg_color);
            }
            wymus_odswiezanie = 0;
        }

        // Krok B: Odświeżanie "żywych" danych zależy od tego, co oglądamy
        if (tryb_ekranu == 0) {
            // TRYB 0: Stary, klasyczny ekran licznika
            sprintf(buf_licznik, "%-3d", liczba_osob); // %-3d zapobiega duchom
            oled_fillRect(1, 20, 96, 16, bg_color);
            oled_putString(40, 20, (uint8_t*)buf_licznik, fg_color, bg_color);
        }
        else {
            // TRYB 1: Ekran logów i czasu
            RTC_TIME_Type aktualny_czas;
            get_current_time(&aktualny_czas);

            // Wyświetlamy aktualnie biegnący czas (odświeża się bez mrugania ekranu)
            char buf_czas[25];
            sprintf(buf_czas, "Teraz: %02d:%02d:%02d", aktualny_czas.HOUR, aktualny_czas.MIN, aktualny_czas.SEC);
            oled_putString(1, 16, (uint8_t*)buf_czas, fg_color, bg_color);

            // Wyświetlamy czas krytycznego zdarzenia
            if (bylo_przepelnienie) {
                char buf_log[25];
                sprintf(buf_log, "Alarm: %02d:%02d:%02d", ost_przepelnienie.HOUR, ost_przepelnienie.MIN, ost_przepelnienie.SEC);
                oled_putString(1, 31, (uint8_t*)buf_log, fg_color, bg_color);

            } else {
                // Gdy po restarcie prądu jeszcze nikt nie przekroczył limitu
                oled_putString(1, 31, (uint8_t*)"Brak przepelnienia", fg_color, bg_color);
            }
        }

        Timer0_Wait(50);
    }

    return 0;
}
