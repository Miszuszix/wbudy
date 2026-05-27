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
#include "rtc_clock/rtc_clock.h" 

#define LASER1 6U
#define LASER2 8U
#define SW3_PORT 0U
#define SW3_PIN 4U

void check_failed(uint8_t *file, uint32_t line);

void check_failed(uint8_t *file, uint32_t line) {
    (void)file;
    (void)line;
    while(1) {
    }
}

int main(void) {
    init_ssp();
    oled_init();
    init_audio();
    init_led_bar();
    init_light_sensor();
    init_rtc(); 

    if (SysTick_Config(SystemCoreClock / 1000U) != 0U) {
        while (1) {
        }
    }

    GPIO_SetDir(2, (uint32_t)1U << 0U, 1);
    GPIO_SetDir(2, (uint32_t)1U << 1U, 1);
    GPIO_SetDir(0, (uint32_t)1U << 27U, 1);
    GPIO_SetDir(0, (uint32_t)1U << 28U, 1);
    GPIO_SetDir(2, (uint32_t)1U << 13U, 1);

    GPIO_ClearValue(0, (uint32_t)1U << 27U);
    GPIO_ClearValue(0, (uint32_t)1U << 28U);
    GPIO_ClearValue(2, (uint32_t)1U << 13U);

    GPIO_SetDir(2, ((uint32_t)1U << LASER1), 0);
    GPIO_SetDir(2, ((uint32_t)1U << LASER2), 0);
    GPIO_SetDir(SW3_PORT, ((uint32_t)1U << SW3_PIN), 0);

    init_counter_memory();
    int liczba_osob = load_saved_counter();
    int max_osob = 5;

    int stan = 0;
    uint32_t czas_startu = 0U;

    int aktualny_tryb_jasnosci = -1;
    uint32_t bg_color = OLED_COLOR_WHITE;
    uint32_t fg_color = OLED_COLOR_BLACK;

    int tryb_ekranu = 0;           
    int wymus_odswiezanie = 1;     
    uint32_t ostatnie_klikniecie = 0U; 

    RTC_TIME_Type ost_przepelnienie;
    int bylo_przepelnienie = 0;

    char buf_licznik[15];
    char buf_limit[20];
    
    (void)sprintf(buf_limit, "Limit: %d", max_osob);

    uint8_t txt_licznik[] = {'L','i','c','z','n','i','k',' ','O','s','o','b',':','\0'};
    uint8_t txt_system[]  = {'S','y','s','t','e','m',' ','C','z','a','s','u',':','\0'};
    uint8_t txt_brak[]    = {'B','r','a','k',' ','p','r','z','e','p','e','l','n','i','e','n','i','a','\0'};

    while(1) {

        int nowy_tryb_jasnosci = is_dark_mode();
        if (nowy_tryb_jasnosci != aktualny_tryb_jasnosci) {
            aktualny_tryb_jasnosci = nowy_tryb_jasnosci;
            wymus_odswiezanie = 1; 

            if (aktualny_tryb_jasnosci == 1) { 
                bg_color = OLED_COLOR_BLACK;
                fg_color = OLED_COLOR_WHITE;
            } else {                  
                bg_color = OLED_COLOR_WHITE;
                fg_color = OLED_COLOR_BLACK;
            }
        }

        int sw3_state = ((GPIO_ReadValue(SW3_PORT) & ((uint32_t)1U << SW3_PIN)) == 0U) ? 1 : 0;

        if ((sw3_state == 1) && ((getTicks() - ostatnie_klikniecie) > 300U)) {
            ostatnie_klikniecie = getTicks();
            
            if (tryb_ekranu == 0) {
                tryb_ekranu = 1;
            } else {
                tryb_ekranu = 0;
            }
            
            wymus_odswiezanie = 1;      
        }

        uint32_t port2_state = GPIO_ReadValue(2);
        int laser1 = ((port2_state & ((uint32_t)1U << LASER1)) != 0U) ? 1 : 0;
        int laser2 = ((port2_state & ((uint32_t)1U << LASER2)) != 0U) ? 1 : 0;

        if (stan == 0) {
            if (laser1 == 1) {
                czas_startu = getTicks();
                stan = 1;
            } else if (laser2 == 1) {
                czas_startu = getTicks();
                stan = 2;
            } else {
            }
        } else if (stan == 1) {
            if ((getTicks() - czas_startu) > 2000U) {
                stan = 0;
            } else if (laser2 == 1) {
                liczba_osob++;
                save_counter(liczba_osob);
                if (liczba_osob > max_osob) {
                    playSong(2); 
                    get_current_time(&ost_przepelnienie); 
                    bylo_przepelnienie = 1;
                } else {
                    playSong(0);
                }
                stan = 3;
            } else {
            }
        } else if (stan == 2) {
            if ((getTicks() - czas_startu) > 2000U) {
                stan = 0;
            } else if (laser1 == 1) {
                if (liczba_osob > 0) {
                    liczba_osob--;
                    save_counter(liczba_osob);
                    playSong(1);
                }
                stan = 3;
            } else {
            }
        } else if (stan == 3) {
            if ((laser1 == 0) && (laser2 == 0)) {
                stan = 0;
            }
        } else {
            stan = 0;
        }

        update_led_bar(liczba_osob);

        if (wymus_odswiezanie == 1) {
            oled_clearScreen(bg_color);
            if (tryb_ekranu == 0) {
                oled_putString(1, 1, txt_licznik, fg_color, bg_color);
                oled_putString(1, 40, (uint8_t*)buf_limit, fg_color, bg_color);
            } else {
                oled_putString(1, 1, txt_system, fg_color, bg_color);
            }
            wymus_odswiezanie = 0;
        }

        if (tryb_ekranu == 0) {
            (void)sprintf(buf_licznik, "%-3d", liczba_osob); 
            oled_fillRect(1, 20, 96, 16, bg_color);
            oled_putString(40, 20, (uint8_t*)buf_licznik, fg_color, bg_color);
        }
        else {
            RTC_TIME_Type aktualny_czas;
            get_current_time(&aktualny_czas);

            char buf_czas[25];
            (void)sprintf(buf_czas, "Teraz: %02d:%02d:%02d", (int)aktualny_czas.HOUR, (int)aktualny_czas.MIN, (int)aktualny_czas.SEC);
            oled_putString(1, 16, (uint8_t*)buf_czas, fg_color, bg_color);

            if (bylo_przepelnienie == 1) {
                char buf_log[25];
                (void)sprintf(buf_log, "Alarm: %02d:%02d:%02d", (int)ost_przepelnienie.HOUR, (int)ost_przepelnienie.MIN, (int)ost_przepelnienie.SEC);
                oled_putString(1, 31, (uint8_t*)buf_log, fg_color, bg_color);

            } else {
                oled_putString(1, 31, txt_brak, fg_color, bg_color);
            }
        }

        Timer0_Wait(50);
    }

    return 0;
}