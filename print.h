#pragma once

#ifndef _PRINT_H_
#define _PRINT_H_

#define PIECE_BACK_COLOR back_color_green
#define BOARD_BACK_COLOR back_color_white
#define GUIDE_LINE_BACK_COLOR back_color_grey
#define FRAME_ON_COLOR txt_color_yellow
#define CURSOR_COLOR back_color_yellow

void clear_console();
void first_console_setting();
void print_game_board_frame();
void print_current_pieces();
void print_guide_line_on_the_board();
void print_guide_line_from_moveable_pos();
extern int moveable_pos[8][8];

void print_turn();
void print_side_info();
void print_main_menu_frame();
void print_promote_frame();

void print_promote_window();

#endif