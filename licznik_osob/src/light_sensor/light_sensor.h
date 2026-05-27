#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <stdint.h>

/**
 * @brief Inicjalizuje czujnik natężenia światła.
 */
void init_light_sensor(void);

/**
 * @brief Analizuje natężenie światła i decyduje o aktywnym trybie jasności ekranu.
 *
 * Funkcja wykorzystuje algorytm z histerezą, aby zapobiec migotaniu interfejsu
 * w warunkach pośredniego oświetlenia.
 *
 * @return 1 jeśli aktywowano tryb nocny, 0 jeśli tryb dzienny.
 */
int is_dark_mode(void);

/**
 * @brief Zwraca surowy pomiar natężenia światła z przetwornika ADC.
 *
 * @return Wartość natężenia oświetlenia w postaci liczby całkowitej.
 */
uint32_t get_raw_light(void);

#endif