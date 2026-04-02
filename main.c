#include <reg52.h>

typedef unsigned char u8;
typedef unsigned int  u16;

sbit LCD_RS = P2^6; //½Ó¿Ú
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;

void lcd_delay_ms(u16 ms)
{
    u16 i,j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 110; j++);
}

void lcd_write_cmd(u8 cmd) //ÅäÖÃ¼Ä´æÆ÷
{
    LCD_RS = 0;
    LCD_RW = 0;
    P0 = cmd;
    LCD_EN = 1;
    lcd_delay_ms(1);
    LCD_EN = 0;
}

void lcd_write_dat(u8 dat)
{
    LCD_RS = 1;
    LCD_RW = 0;
    P0 = dat;
    LCD_EN = 1;
    lcd_delay_ms(1);
    LCD_EN = 0;
}

void lcd_init(void)
{
    lcd_write_cmd(0x38);  
    lcd_write_cmd(0x0C);  
    lcd_write_cmd(0x06);  
    lcd_write_cmd(0x01);  
    lcd_delay_ms(5);
}

void lcd_set_cgram(u8 addr, u8 *tab)
{
    u8 i;
    lcd_write_cmd(0x40 + addr * 8);
    for(i = 0; i < 8; i++)
    {
        lcd_write_dat(tab[i]);
    }
}


const u8 panda_open[4][8] = {
   
    {0x0E, 0x1F, 0x11, 0x11, 0x1F, 0x11, 0x0E, 0x00},
   
    {0x0E, 0x1F, 0x11, 0x11, 0x1F, 0x11, 0x0E, 0x00},
   
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x0E, 0x00},
   
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x0E, 0x00}
};


const u8 panda_close[4][8] = {
   
    {0x0E, 0x1F, 0x11, 0x1F, 0x11, 0x0E, 0x00},
      
    {0x0E, 0x1F, 0x1F, 0x11, 0x1F, 0x11, 0x0E, 0x00},
  
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x0E, 0x00},
    
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x0E, 0x00}
};


void main(void)
{
    u8 frame = 0;
    u8 i;

    lcd_init();

    for(i = 0; i < 4; i++)
        lcd_set_cgram(i, (u8*)panda_open[i]);

    while(1)
    {
       
        lcd_write_cmd(0x80);
        lcd_write_dat(0); lcd_write_dat(1);
        lcd_write_cmd(0xC0);
        lcd_write_dat(2); lcd_write_dat(3);

        lcd_delay_ms(500);

       
        frame = !frame;
        if(frame)
            for(i=0; i<4; i++) lcd_set_cgram(i, (u8*)panda_close[i]);
        else
            for(i=0; i<4; i++) lcd_set_cgram(i, (u8*)panda_open[i]);
    }
}
