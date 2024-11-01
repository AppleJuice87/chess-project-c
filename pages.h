#pragma once

#ifndef _PAGES_H_
#define _PAGES_H_

enum { NEW_GAME=1, CONTINUE_GAME, EXIT };
void goto_main_menu_page();
void goto_game_page();
void goto_file_error_page();
void goto_game_over_page();
void goto_exit_page();

enum { GAME_BOARD=1, SIDE_MENU };
extern int where_is_cursor;

#endif 