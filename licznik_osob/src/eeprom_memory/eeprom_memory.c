#include "eeprom_memory.h"
#include <stdint.h>
#include "eeprom.h" // Biblioteka EaBaseBoard

// Definiujemy, w którym miejscu (adresie) w pamięci trzymamy nasz wynik.
// EEPROM to taka długa szafka, wybieramy pierwszą szufladę (0x00).
#define COUNTER_ADDR 0x00

void init_counter_memory(void) {
    // Inicjalizacja sprzętowa układu EEPROM
    eeprom_init();
}

int load_saved_counter(void) {
        read_value = 0U;
    uint8_t read_value = 0;

    // Czytamy 1 bajt danych z naszej szuflady (COUNTER_ADDR)
    eeprom_read((uint8_t*)&read_value, COUNTER_ADDR, 1);

    // Zabezpieczenie: jeśli EEPROM jest całkowicie pusty (0xFF),
    // to zakładamy, że to pierwsze uruchomienie i licznik to 0.
    if (read_value > 20U) {
        save_counter(0);
        read_value = 0U;
    }

    return (int)read_value;
}

void save_counter(int count) {
    // Rzutujemy naszego inta na mniejszego, 8-bitowego inta, bo
    // nasz licznik i tak nigdy nie przekroczy 255 osób.
    uint8_t value_to_write = (uint8_t)count;

    // Zapisujemy 1 bajt do szuflady
    eeprom_write((uint8_t*)&value_to_write, COUNTER_ADDR, 1);
}
