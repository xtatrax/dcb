
#include "../mcc_generated_files/system/system.h"
#include "TinyRTC.h"

uint8_t bcd2dec(uint8_t val)
{
    return (val >> 4) * 10 + (val & 0x0F);
}

bool i2c_scan(uint8_t addr) {
    uint8_t dummy = 0x00;

    if(!I2C1_Write(addr, &dummy, 1))
        return false;

    while(I2C1_IsBusy());

    return (I2C1_ErrorGet() == I2C_ERROR_NONE);
}

bool rtc_read_reg(uint8_t reg, uint8_t *val, size_t len) {
    if(!I2C1_WriteRead(0x68, &reg, 1, val, len))
        return false;

    while(I2C1_IsBusy());

    return (I2C1_ErrorGet() == I2C_ERROR_NONE);
}

bool rtc_read(tmElements_t *tm)
{
    uint8_t reg = 0x00;
    uint8_t buf[7] = {0};

    // if(!I2C1_Write(0x68 << 1, &reg, 1))
    //     return false;
    // while(I2C1_IsBusy()); // 安全待ち
    // if(!I2C1_Read(0x68 << 1, buf, 7))
    //     return false;
    // while(I2C1_IsBusy()); // 安全待ち
    if(!rtc_read_reg(reg, buf, 7))
        return false;
    tm->Second = bcd2dec(buf[0] & 0x7F);
    tm->Minute = bcd2dec(buf[1]);
    tm->Hour   = bcd2dec(buf[2] & 0x3F);
    tm->Wday   = bcd2dec(buf[3]);
    tm->Day    = bcd2dec(buf[4]);
    tm->Month  = bcd2dec(buf[5]);
    tm->Year   = bcd2dec(buf[6]);

    return true;
}

// // デバッグ用: I2Cバススキャン
// bool i2c_scan(uint8_t addr) {
//     uint8_t dummy = 0;
//     return I2C1_Write(addr << 1, &dummy, 0); // 書き込みテスト
// }

// // デバッグ用: RTCレジスタ直接読み取り
// bool rtc_read_reg(uint8_t reg, uint8_t *val) {
//     if(!I2C1_Write(0x68 << 1, &reg, 1))
//         return false;
//     return I2C1_Read(0x68 << 1, val, 1);
// }