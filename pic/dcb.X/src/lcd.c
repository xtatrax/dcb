/*
 * File:   lcd.c
 * Author: xtatrax & ChatGPT
 *
 * Created on March 27, 2026, 3:45 PM
 */

#include "../mcc_generated_files/system/system.h"

#include "./lcd.h"

void lcd_send4(unsigned char data){
    D4 = (data >> 0) & 1;
    D5 = (data >> 1) & 1;
    D6 = (data >> 2) & 1;
    D7 = (data >> 3) & 1;

    EN = 1;
    __delay_us(1);
    EN = 0;
}
void lcd_cmd(unsigned char cmd){

    RS = 0;

    lcd_send4(cmd >> 4);
    lcd_send4(cmd & 0x0F);

    __delay_ms(2);
}

void lcd_data(unsigned char data){

    RS = 1;

    lcd_send4(data >> 4);
    lcd_send4(data & 0x0F);

    __delay_ms(2);
}
void lcd_init(){

    __delay_ms(20);

    RS = 0;

    lcd_send4(0x03);
    __delay_ms(5);

    lcd_send4(0x03);
    __delay_us(100);

    lcd_send4(0x03);

    lcd_send4(0x02);

    lcd_cmd(0x28); // 4bit 2line
    lcd_cmd(0x0C); // display on
    lcd_cmd(0x06); // entry
    lcd_cmd(0x01); // clear
}
void lcd_print(char *str){

    while(*str){
        lcd_data(*str++);
    }
}
