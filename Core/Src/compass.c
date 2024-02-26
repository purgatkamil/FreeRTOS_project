#include "compass.h"

#define I2C_ADDRESS 0x3C

#define CRA_REG 0x00
#define CRB_REG 0x01
#define MODE_REG 0x02
#define DATA_REG 0x03

void writeToRegister(uint8_t reg, uint8_t value) {
    uint8_t buffer[2] = {reg, value};
    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDRESS << 1, buffer, 2, HAL_MAX_DELAY);
}

uint16_t readFromRegister(uint8_t reg) {
    uint8_t buffer[2] = {0};

    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDRESS << 1, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, (I2C_ADDRESS << 1) | 0x01, buffer, 2, HAL_MAX_DELAY);

    return (buffer[0] << 8) | buffer[1];
}

int16_t convertToDecimal(uint16_t value) {
	 // Konwersja 2's complement na wartość ze znakiem
	    int16_t result = (int16_t)value;

	    // Wartość ujemna, dokonaj rozszerzenia znaku
	    if (result & 0x8000) {
	        result |= 0xFFFF0000;
	    }

	    return result;
}

void singleMeasurement(int16_t result[3]) {
    // Inicjalizacja kroku 1-2
    writeToRegister(CRA_REG, 0x70);
    writeToRegister(CRB_REG, 0xA0);

        // Rozpoczęcie pojedynczego pomiaru (krok 3)
        writeToRegister(MODE_REG, 0x01);

        // Oczekiwanie 6 ms (krok 4)
        HAL_Delay(6);

        // Odczyt danych (krok 5)
        writeToRegister(DATA_REG, 0x06);
        uint16_t rawData = readFromRegister(DATA_REG);

        // Konwersja na wartości X, Y, Z (krok 6)
        result[0] = convertToDecimal(rawData >> 8);
        result[1] = convertToDecimal(rawData & 0xFF);

        // Przejście do następnego rejestru danych (krok 7)
        writeToRegister(MODE_REG, 0x03);

        // Oczekiwanie na zakończenie pomiaru (krok 8)
        while (readFromRegister(MODE_REG) & 0x01) {
            // Oczekiwanie na zakończenie pomiaru
        }

        // Zapisz wyniki do result[2] (możesz dostosować, jeśli istnieje oddzielna wartość Y w danych)
        result[2] = 0;  // Przykład, dostosuj do swojej konfiguracji

}

