#ifndef _st7735s_h
#define _st7735s_h

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define  TFT_A0_GPIO_Port      GPIOA
#define  TFT_A0_Pin            GPIO_PIN_4

#define  SPI2_CS_GPIO_Port     GPIOA
#define  SPI2_CS_Pin           GPIO_PIN_6

#define  TFT_RESET_GPIO_Port   GPIOA
#define  TFT_RESET_Pin         GPIO_PIN_3

#define  TFT_BL_PORT           GPIOC
#define  TFT_BL_PIN            GPIO_PIN_4



void lcd_clear(void);
void lcd_init(void);
void lcd_show(void);
void set_color(u16 c);
void lcd_point(u16 x,u16 y);
void lcd_str(char * str,u16 x,u16 y);
void lcd_num(long n,u16 x,u16 y);
void lcd_box(u8 x,u8 y,u8 w,u8 h);
void lcd_color_fill(u8 x1,u8 y1,u8 x2,u8 y2,u16 *color_p);
void lcd_color_fill_int(u8 x1,u8 y1,u8 x2,u8 y2,u16 color_p);

#endif
