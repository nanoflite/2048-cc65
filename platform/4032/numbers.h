#ifndef __NUMBERS_H__
#define __NUMBERS_H__

extern unsigned char numbers_data[];  

extern void numbers_set_screen(char *screen);
extern void numbers_digit_xy_condensed(char digit, char x, char y);
extern void numbers_digit_xy(char digit, char x, char y);
extern void numbers_number_xy(unsigned int value, char x, char y);
extern void numbers_number_xy_condensed(unsigned int value, char x, char y);

extern void numbers_hline(unsigned char x, unsigned char y, unsigned length);
extern void numbers_vline(unsigned char x, unsigned char y, unsigned length);

extern void numbers_clear_rect(unsigned char x, unsigned char y, unsigned char number_of_digits);

#endif
