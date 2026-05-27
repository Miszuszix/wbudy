#ifndef LED_BAR_H
#define LED_BAR_H

/**
 * @brief Inicjalizuje sprzętową linijkę diodową.
 *
 * Konfiguruje piny P0.10 i P0.11 do obsługi magistrali I2C2 oraz
 * inicjalizuje układ sterownika PCA9532 znajdujący się na płycie.
 */
void init_led_bar(void);

/**
 * @brief Aktualizuje stan linijki diodowej na podstawie liczby osób.
 *
 * Używa operacji bitowych do zapalenia liczby diod odpowiadającej 
 * przekazanemu parametrowi. Posiada zabezpieczenie przed przekroczeniem 
 * fizycznej ilości diod (maksymalnie 16).
 *
 * @param liczba_osob Aktualna liczba osób w pomieszczeniu.
 */
void update_led_bar(int liczba_osob);

#endif