/*
 * RamEEPROM.h
 *
 *  Created on: 2015年1月19日
 *      Author: taoyuan
 */

#ifndef RamEEPROM_H_
#define RamEEPROM_H_

#include "Arduino.h"
#include "RamBaseDevice.h"

#if defined(__AVR_ATmega644P__)
#define BLOCK_COUNT	(4)	// 2KB
#elif defined(__AVR_ATmega1284P__)
#define BLOCK_COUNT	(8)	// 4KB
#else
#define BLOCK_COUNT	(1)	// 512B
#endif

class RamEEPROM: public RamBaseDevice {
public:
	RamEEPROM(uint8_t blockCount = BLOCK_COUNT) :
			m_blockCount(blockCount) {
	}
	virtual ~RamEEPROM() {
	}

	uint32_t sizeBlocks() {
		return m_blockCount;
	}

	/** Read a block from the EEPROM.
	 * \param[in] address start location in the EEPROM.
	 * \param[out] buf location in Arduino SRAM for the transfer.
	 * \param[in] nbyte number of bytes to transfer.
	 * \return true unless address is out of range.
	 */
	bool read(uint32_t address, void *buf, size_t nbyte);

	/** Write a block to the EEPROM.
	 * \param[in] address start location in the EEPROM.
	 * \param[in] buf location in Arduino SRAM for the transfer.
	 * \param[in] nbyte number of bytes to transfer.
	 * \return true unless address is out of range.
	 */
	bool write(uint32_t address, const void *buf, size_t nbyte);
protected:
	uint8_t m_blockCount;
};

#endif /* RamEEPROM_H_ */
