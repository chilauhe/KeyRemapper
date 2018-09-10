#ifndef __CRC32_H__
#define __CRC32_H__ 1
#include "heact.h"

uint8_t crc8_notbl(uint8_t *p, size_t len);

#ifdef HAVE_CRC32
extern  const uint32_t  crc32_table256[];
static inline uint32_t
crc32(uint8_t *p, size_t len)
{
	//POLY 0x04C11DB7
    uint32_t  crc = 0xffffffff;
    while (len--) {
        crc = (crc >> 8) ^ crc32_table256[(crc ^ *p++) & 0xff];
    }

    return crc ^ 0xffffffff;
}
#else
static inline uint32_t
crc32(uint8_t *p, size_t len)
{
	return 0;
}
#endif

#ifdef HAVE_CRC8
extern const uint8_t crc8table[];
static inline uint8_t crc8(uint8_t *p, size_t len)
{
   //poly 0x07
   uint8_t crc = 0x00;
   while(len--){
      crc = crc8table[*p++ ^ crc];
   }
   return crc;
}
#else
static inline uint8_t
crc8(uint8_t *p, size_t len)
{
	return 0;
}
#endif

#ifdef HAVE_CRC16
extern const uint16_t crc16_ibm_table[];
static inline uint16_t crc16(uint8_t const *buffer, size_t len)
{
	//poly 0x8005,crc-16/arc
	uint16_t crc = 0;
	while (len--) {
		crc = (crc >> 8) ^ crc16_ibm_table[(crc ^ *buffer++) & 0xFF];
	}
	return crc;
}
#else
static inline uint16_t
crc16(uint8_t *p, size_t len)
{
	return 0;
}
#endif

#endif