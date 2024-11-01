#include "all_headers.h"

int load_game_data()
{
    FILE *fp = fopen("save.dat", "rb");

    if(fp == NULL) return 0;
    
    STRUCT_FOR_SAVE data;
    fread(&data, sizeof(STRUCT_FOR_SAVE), 1, fp);

    turn = data.turn_d;
    is_on_game_now = data.is_on_game_now_d;
    current_chess_board = data.board_d;

    fclose(fp);

    if(is_on_game_now == 0) return 0;
    else
    return 1;
}

void save_game_data()
{
    FILE *fp = fopen("save.dat", "wb");

    STRUCT_FOR_SAVE data;
    data.turn_d = turn;
    data.is_on_game_now_d = is_on_game_now;
    data.board_d = current_chess_board;

    fwrite(&data, sizeof(STRUCT_FOR_SAVE), 1, fp);

    fclose(fp);
}