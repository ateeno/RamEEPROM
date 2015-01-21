/*
 * RamEEPROM.cpp
 *
 *  Created on: 2015年1月19日
 *      Author: taoyuan
 */

#include "RamEEPROM.h"

#ifdef __arm__ // should provide EEPROM implementation in ARM
#include "EEPROM.h"

uint8_t eeprom_read(int address) {
	return EEPROM.read(address);
}

void eeprom_write(int address, uint8_t value) {
	EEPROM.write(address, value);
}

#else // use avr/eeprom
#include "avr/eeprom.h"

uint8_t eeprom_read(uint32_t address) {
	return eeprom_read_byte((unsigned char *) address);
}

void eeprom_write(uint32_t address, uint8_t value) {
	eeprom_write_byte((unsigned char *) address, value);
}

#endif

bool RamEEPROM::read(uint32_t address, void* buf, size_t nbyte) {
	uint8_t* dst = reinterpret_cast<uint8_t*>(buf);
	for (uint32_t i = 0; i < nbyte; i++) {
		dst[i] = eeprom_read(address + i);
	}
	return true;
}

bool RamEEPROM::write(uint32_t address, const void* buf, size_t nbyte) {
	const uint8_t* src = reinterpret_cast<const uint8_t*>(buf);
	for (uint32_t i = 0; i < nbyte; i++) {
		eeprom_write(address + i, src[i]);
	}
	return true;
}
