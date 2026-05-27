#ifndef SPI_SETUP_H
#define SPI_SETUP_H

/**
 * @brief Inicjalizuje interfejs komunikacyjny SSP (SPI).
 *
 * Konfiguruje linie zegarowe i linie danych wymagane do prawidłowej 
 * komunikacji z wyświetlaczem graficznym OLED umieszczonym na płycie.
 */
void init_ssp(void);

#endif