#ifndef LED_BAR_H
#define LED_BAR_H

// Inicjalizacja układu i magistrali I2C
void init_led_bar(void);

// Funkcja aktualizująca pasek. Przyjmuje aktualną liczbę osób.
void update_led_bar(int liczba_osob);

#endif
