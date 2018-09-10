#ifndef __BASE_90_H__
#define __BASE_90_H__ 1

char u8base90(uint8_t val,char *buf);
char u16base90(uint16_t val,char *buf);
char u32base90(uint32_t val, char *buf, uint8_t len);
uint32_t base90u32(char *buf, size_t len);

#endif