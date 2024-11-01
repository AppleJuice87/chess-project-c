#pragma once

#ifndef _GAME_H_
#define _GAME_H_

typedef struct _cursor{
    int x;
    int y;
} CURSOR_POS;
extern CURSOR_POS game_board_cursor_pos;

void set_new_game();
int pos_x(int x);

int board_pos_x(int x);
int board_pos_y(int y);

typedef struct _chess_board{
    char piece[8][8];
    int info[8][8];
} CHESS_BOARD;

typedef struct _struct_for_save{
    int turn_d;
    int is_on_game_now_d;
    CHESS_BOARD board_d;
} STRUCT_FOR_SAVE;

extern CHESS_BOARD new_chess_board;
extern CHESS_BOARD current_chess_board;

extern int turn;
extern int is_on_game_now;
extern char key_input;
extern int main_menu_cursor_pos;

void turn_change();
int is_enemy(int x, int y);
int is_enemy_current();
int is_my_piece(int x, int y);
int is_my_piece_current();
void move_cursor_in_main_menu();
void move_cursor_in_game_board();

void guide_line_logic_Pawn();
void guide_line_logic_Rook();
void guide_line_logic_Knight();
void guide_line_logic_Bishop();
void guide_line_logic_Queen();
void guide_line_logic_King();

void clear_moveable_pos();
void move_piece(CURSOR_POS from_a, CURSOR_POS to_b);

int is_pos_in_board(int x, int y);
int count_moveable_pos();

int is_game_over();
void check_pawn();
void promote_pawn(int x, int y);

void move_cursor_in_promote_window();
extern int promo_cur;

#endif