#ifndef EEPROM_MEMORY_H
#define EEPROM_MEMORY_H

/**
 * @brief Inicjalizuje układ pamięci I2C EEPROM.
 *
 * Przygotowuje zewnętrzną pamięć nieulotną na płycie bazowej do zapisu 
 * i odczytu danych za pośrednictwem magistrali I2C.
 */
void init_counter_memory(void);

/**
 * @brief Odczytuje zapisaną liczbę osób z pamięci EEPROM.
 *
 * Funkcja posiada wbudowane zabezpieczenie logiczne: jeśli odczytana wartość
 * jest większa niż 20, automatycznie czyści pamięć i zwraca wartość początkową 0.
 *
 * @return Zapisana liczba osób (w zakresie 0-20).
 */
int load_saved_counter(void);

/**
 * @brief Zapisuje aktualną liczbę osób do pamięci nieulotnej EEPROM.
 *
 * @param count Liczba osób do fizycznego zapisania w układzie pamięci.
 */
void save_counter(int count);

#endif