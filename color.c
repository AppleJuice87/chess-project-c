#include "all_headers.h"

WORD back_color_black = 0; 
WORD back_color_yellow = BACKGROUND_RED | BACKGROUND_GREEN;
WORD back_color_white = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
WORD back_color_blue = BACKGROUND_BLUE;
WORD back_color_brown = BACKGROUND_RED | BACKGROUND_GREEN;
WORD back_color_green = BACKGROUND_GREEN;
WORD back_color_grey = BACKGROUND_INTENSITY;

WORD txt_color_black = 0;
WORD txt_color_red = FOREGROUND_RED;
WORD txt_color_green = FOREGROUND_GREEN;
WORD txt_color_yellow = FOREGROUND_RED | FOREGROUND_GREEN;
WORD txt_color_white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
WORD txt_color_brown = FOREGROUND_RED | FOREGROUND_GREEN;
WORD txt_color_grey = FOREGROUND_INTENSITY;
WORD txt_color_blue = FOREGROUND_BLUE;

WORD txt_bold = FOREGROUND_INTENSITY;

void set_color(WORD txt_color, WORD back_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt_color | back_color);
}

void reset_color()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt_color_white | back_color_black | txt_bold);
}