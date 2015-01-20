/*
 * RamEEPROM.cpp
 *
 *  Created on: 2015年1月19日
 *      Author: taoyuan
 */

#include <RamEEPROM.h>
#include "EEPROM.h"

bool RamEEPROM::read(uint32_t address, void* buf, size_t nbyte) {
	uint8_t* dst = reinterpret_cast<uint8_t*>(buf);
	for (uint32_t i = 0; i < nbyte; i++) {
		dst[i] = EEPROM.read(address + i);
	}
	return true;
}

bool RamEEPROM::write(uint32_t address, const void* buf, size_t nbyte) {
	const uint8_t* src = reinterpret_cast<const uint8_t*>(buf);
	for (uint32_t i = 0; i < nbyte; i++) {
		EEPROM.write(address + i, src[i]);
	}
	return true;
}
