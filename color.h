#pragma once

#ifndef _COLOR_H_
#define _COLOR_H_

#include "common.h"

extern WORD back_color_black;
extern WORD back_color_yellow;
extern WORD back_color_white;
extern WORD back_color_blue;
extern WORD back_color_brown;
extern WORD back_color_green;
extern WORD back_color_grey;

extern WORD txt_color_black;
extern WORD txt_color_red;
extern WORD txt_color_green;
extern WORD txt_color_yellow;
extern WORD txt_color_white;
extern WORD txt_color_brown;
extern WORD txt_color_grey;
extern WORD txt_color_blue;

extern WORD txt_bold;

void set_color(WORD txt_color, WORD back_color);
void reset_color();

#endif