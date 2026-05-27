#ifndef EEPROM_MEMORY_H
#define EEPROM_MEMORY_H

// Inicjalizacja komunikacji z pamięcią
void init_counter_memory(void);

// Odczytanie zapisanej wartości ze wskazanej komórki
int load_saved_counter(void);

// Zapisanie nowej wartości (wywołujemy tylko przy zmianie!)
void save_counter(int count);

#endif
