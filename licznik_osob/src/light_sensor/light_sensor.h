#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

// Uruchamia czujnik światła na I2C
void init_light_sensor(void);

// Zwraca 0 dla Dnia, 1 dla Nocy
int is_dark_mode(void);

// NOWA FUNKCJA DO DEBUGOWANIA
uint32_t get_raw_light(void);

#endif
