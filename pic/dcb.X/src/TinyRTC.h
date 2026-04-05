#ifndef XC_HEADER_TINYRTC_H
#define	XC_HEADER_TINYRTC_H
typedef struct  { 
  uint8_t Second; 
  uint8_t Minute; 
  uint8_t Hour; 
  uint8_t Wday;   // day of week, sunday is day 1
  uint8_t Day;
  uint8_t Month; 
  uint8_t Year;   // offset from 1970; 
} 	tmElements_t, TimeElements, *tmElementsPtr_t;

uint8_t bcd2dec(uint8_t val);
bool rtc_read(tmElements_t *tm);
bool i2c_scan(uint8_t addr);
bool rtc_read_reg(uint8_t reg, uint8_t *val, size_t len);

#endif	/* XC_HEADER_TINYRTC_H */