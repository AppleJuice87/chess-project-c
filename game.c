#include "all_headers.h"

char key_input;
int main_menu_cursor_pos = 1;

CHESS_BOARD new_chess_board = {
    {
        {'R','N','B','Q','K','B','N','R'},
        {'P','P','P','P','P','P','P','P'},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'}
    },
    {
        {2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1}
    }
};

int turn;
int is_on_game_now;

CHESS_BOARD current_chess_board;

void set_new_game()
{
    current_chess_board = new_chess_board;
    turn = 1;
    is_on_game_now = 1;
    save_game_data();
}

int pos_x(int x)
{
    return x * 2;
}

int board_pos_x(int x)
{
    return (x-1)*4 + 10;
}

int board_pos_y(int y)
{
    return (2*y) + 1;
}

void turn_change()
{
    if(turn == 1)
    {
        turn = 2;
    } 
    else 
    {
        turn = 1;
    }
}

int is_enemy(int x, int y)
{
    if(current_chess_board.info[y-1][x-1] == 0)
    {
        return -1;
    }
    else if(turn == current_chess_board.info[y-1][x-1])
    {
        return 0;
    } 
    else 
    {
        return 1;
    }
}
int is_enemy_current()
{
    int x = game_board_cursor_pos.x;
    int y = game_board_cursor_pos.y;

    if(current_chess_board.info[y-1][x-1] == 0)
    {
        return -1;
    }
    else if(turn == current_chess_board.info[y-1][x-1])
    {
        return 0;
    } 
    else 
    {
        return 1;
    }
}

void move_cursor_in_main_menu()
{
    key_input = getch();

        switch (key_input)
        {
            case 'w': case 'W':
                if(main_menu_cursor_pos == 1)
                {
                    main_menu_cursor_pos = 3;
                    break;
                } 
                else 
                {
                    main_menu_cursor_pos--;
                    break;
                }
            case 's': case 'S':
                if(main_menu_cursor_pos == 3)
                {
                    main_menu_cursor_pos = 1;
                    break;
                } 
                else 
                {
                    main_menu_cursor_pos++;
                    break;
                }
            case '\r':
                break;
            default:
                break;
        }
}

CURSOR_POS game_board_cursor_pos = { 4, 4 };

void move_cursor_in_game_board()
{
    key_input = getch();
    switch (key_input)
    {
        case 'w': case 'W':
            if(game_board_cursor_pos.y == 1)
            {
                game_board_cursor_pos.y = 8;
                break;
            } 
            else 
            {
                game_board_cursor_pos.y--;
                break;
            }
        case 's': case 'S':
            if(game_board_cursor_pos.y == 8)
            {
                game_board_cursor_pos.y = 1;
                break;
            } 
            else 
            {
                game_board_cursor_pos.y++;
                break;
            }
        case 'a': case 'A':
            if(game_board_cursor_pos.x == 1)
            {
                game_board_cursor_pos.x = 8;
                break;
            } 
            else 
            {
                game_board_cursor_pos.x--;
                break;
            }
        case 'd': case 'D':
            if(game_board_cursor_pos.x == 8)
            {
                game_board_cursor_pos.x = 1;
                break;
            } 
            else 
            {
                game_board_cursor_pos.x++;
                break;
            }
        case '\r':
            
            break;
        default:
            break;
    }
}

void clear_moveable_pos()
{
    int a,b;

    for(a=0; a<8; a++)
    {
        for(b=0; b<8; b++)
        {
            moveable_pos[a][b] = 0;
        }
    }
}

int is_my_piece(int x, int y)
{
    if(current_chess_board.info[y-1][x-1] == turn)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int is_my_piece_current()
{
    int x = game_board_cursor_pos.x;
    int y = game_board_cursor_pos.y;

    if(current_chess_board.info[y-1][x-1] == turn)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void guide_line_logic_Pawn()
{
    int x = game_board_cursor_pos.x;
    int y = game_board_cursor_pos.y;

    if (turn == 1)
    {
        if(is_enemy(x,y-1) == -1 && is_pos_in_board(x,y-1) == 1)
        {
            moveable_pos[(y-1)-1][(x-1)] = 1;
        }
        if(is_enemy(x-1,y-1) == 1 && is_pos_in_board(x-1,y-1) == 1)
        {
            moveable_pos[(y-1)-1][(x-1)-1] = 1;
        }
        if(is_enemy(x+1,y-1) == 1 && is_pos_in_board(x+1,y-1) == 1)
        {
            moveable_pos[(y-1)-1][(x-1)+1] = 1;
        }

        if((y == 7) && (is_enemy(x,y-1) == -1) && ( is_enemy(x,y-2) == -1))
        {
            moveable_pos[(y-1)-2][(x-1)] = 1;
        }
    }

    if (turn == 2)
    {
        if(is_enemy(x,y+1) == -1 && is_pos_in_board(x,y+1) == 1)
        {
            moveable_pos[(y-1)+1][(x-1)] = 1;
        }
        if(is_enemy(x-1,y+1) == 1 && is_pos_in_board(x-1,y+1) == 1)
        {
            moveable_pos[(y-1)+1][(x-1)-1] = 1;
        }
        if(is_enemy(x+1,y+1) == 1 && is_pos_in_board(x+1,y+1) == 1)
        {
            moveable_pos[(y-1)+1][(x-1)+1] = 1;
        }

        if((y == 2) && (is_enemy(x,y+1) == -1) && (is_enemy(x,y+2) == -1) )
        {
            moveable_pos[(y-1)+2][(x-1)] = 1;
        }
    }
}

void guide_line_logic_Knight()
{
    int i;
    int x,y;

    x = game_board_cursor_pos.x - 1;
    y = game_board_cursor_pos.y - 2;

    for(i=0; i<3; i+=2)
    {
        if(is_pos_in_board(x+i,y) == 1)
        if(is_my_piece(x+i,y) == 0)
        {
            moveable_pos[y-1][x-1 + i] = 1;
        }
    }

    x = game_board_cursor_pos.x + 2;
    y = game_board_cursor_pos.y - 1;

    for(i=0; i<3; i+=2)
    {
        if(is_pos_in_board(x,y+i) == 1)
        if(is_my_piece(x,y+i) == 0)
        {
            moveable_pos[y-1 + i][x-1] = 1;
        }
    }

    x = game_board_cursor_pos.x - 1;
    y = game_board_cursor_pos.y + 2;

    for(i=0; i<3; i+=2)
    {
        if(is_pos_in_board(x+i,y) == 1)
        if(is_my_piece(x+i,y) == 0)
        {
            moveable_pos[y-1][x-1 + i] = 1;
        }
    }

    x = game_board_cursor_pos.x - 2;
    y = game_board_cursor_pos.y - 1;

    for(i=0; i<3; i+=2)
    {
        if(is_pos_in_board(x,y+i) == 1)
        if(is_my_piece(x,y+i) == 0)
        {
            moveable_pos[y-1 + i][x-1] = 1;
        }
    }
}
void guide_line_logic_Rook()
{
    int x = game_board_cursor_pos.x;
    int y = game_board_cursor_pos.y;

    int i;
    for(i=y-1; i>=1; i--)
    {
        if(is_my_piece(x,i) == 1) break;
        moveable_pos[i-1][x-1] = 1;
        if(is_enemy(x,i) == 1) break;
    }
    for(i=x+1; i<=8; i++)
    {
        if(is_my_piece(i,y) == 1) break;
        moveable_pos[y-1][i-1] = 1;
        if(is_enemy(i,y) == 1) break;
    }
    for(i=y+1; i<=8; i++)
    {
        if(is_my_piece(x,i) == 1) break;
        moveable_pos[i-1][x-1] = 1;
        if(is_enemy(x,i) == 1) break;
    }
    for(i=x-1; i>=1; i--)
    {
        if(is_my_piece(i,y) == 1) break;
        moveable_pos[y-1][i-1] = 1;
        if(is_enemy(i,y) == 1) break;
    }
}

void guide_line_logic_Bishop()
{
    int x = game_board_cursor_pos.x - 1;
    int y = game_board_cursor_pos.y - 1;
    while(is_pos_in_board(x,y) == 1)
    {
        if(is_my_piece(x,y) == 1) break;
        moveable_pos[y-1][x-1] = 1;
        if(is_enemy(x,y) == 1) break;
        x--; y--;
    }

    x = game_board_cursor_pos.x + 1;
    y = game_board_cursor_pos.y - 1;
    while(is_pos_in_board(x,y) == 1)
    {
        if(is_my_piece(x,y) == 1) break;
        moveable_pos[y-1][x-1] = 1;
        if(is_enemy(x,y) == 1) break;
        x++; y--;
    }

    x = game_board_cursor_pos.x + 1;
    y = game_board_cursor_pos.y + 1;
    while(is_pos_in_board(x,y) == 1)
    {
        if(is_my_piece(x,y) == 1) break;
        moveable_pos[y-1][x-1] = 1;
        if(is_enemy(x,y) == 1) break;
        x++; y++;
    }

    x = game_board_cursor_pos.x - 1;
    y = game_board_cursor_pos.y + 1;
    while(is_pos_in_board(x,y) == 1)
    {
        if(is_my_piece(x,y) == 1) break;
        moveable_pos[y-1][x-1] = 1;
        if(is_enemy(x,y) == 1) break;
        x--; y++;
    }
}

void guide_line_logic_Queen()
{
    guide_line_logic_Rook();
    guide_line_logic_Bishop();
}

void guide_line_logic_King()
{
    int x = game_board_cursor_pos.x - 1;
    int y = game_board_cursor_pos.y - 1;

    int i;
    for(i=0; i<3; i++)
    {
        if(is_pos_in_board(x+i,y) == 1 && is_my_piece(x+i,y) != 1)
        moveable_pos[y-1][x-1 + i] = 1;
    }

    y += 2;
    for(i=0; i<3; i++)
    {
        if(is_pos_in_board(x+i,y) == 1 && is_my_piece(x+i,y) != 1)
        moveable_pos[y-1][x-1 + i] = 1;
    }

    y--;
    for(i=0; i<3; i += 2)
    {
        if(is_pos_in_board(x+i,y) == 1 && is_my_piece(x+i,y) != 1)
        moveable_pos[y-1][x-1 + i] = 1;
    }
}

void move_piece(CURSOR_POS A, CURSOR_POS B)
{
    current_chess_board.piece[B.y-1][B.x-1] = current_chess_board.piece[A.y-1][A.x-1];
    current_chess_board.piece[A.y-1][A.x-1] = ' ';

    current_chess_board.info[B.y-1][B.x-1] = current_chess_board.info[A.y-1][A.x-1];
    current_chess_board.info[A.y-1][A.x-1] = 0;
}

int is_pos_in_board(int x, int y)
{
    if(x>=1 && x<=8 && y>=1 && y<=8)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int count_moveable_pos()
{
    int a, b;
    int count = 0;

    for(a=0; a<8; a++)
    for(b=0; b<8; b++)
    if(moveable_pos[a][b] == 1) count++;
    
    return count;
}

int is_game_over()
{
    int a, b;
    int count = 0;

    for(a=0; a<8; a++)
    for(b=0; b<8; b++)
    if(current_chess_board.piece[a][b] == 'K') count++;
    
    if(count == 2) return 0;
    else return 1;
}

void check_pawn()
{
    char _piece;
    int _info;

    if(turn == 1)
    {
        int i;
        for(i=0; i<8; i++)
        {
            _piece = current_chess_board.piece[0][i];
            _info = current_chess_board.info[0][i];
            if(_piece == 'P' && _info == 1)
            {
                promote_pawn(i+1, 1);
                return;
            }
        }
    }
    else if(turn == 2)
    {
        int i;
        for(i=0; i<8; i++)
        {
            _piece = current_chess_board.piece[7][i];
            _info = current_chess_board.info[7][i];
            if(_piece == 'P' && _info == 2)
            {
                promote_pawn(i+1, 8);
                return;
            }
        }
    }
}

int promo_cur;

void promote_pawn(int x, int y)
{
    where_is_cursor = SIDE_MENU;

    print_game_board_frame();
    print_current_pieces();
    print_cursor_on_the_board();

    print_promote_window();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { board_pos_x(x), board_pos_y(y) };
    SetConsoleCursorPosition(hConsole, pos);

    set_color(txt_color_blue, back_color_yellow);
    printf("|P|");
    
    char pieces[4] = {'Q', 'R', 'B', 'N'};
    promo_cur = 0;
    while(1)
    {
        print_promote_window();

        pos.X = board_pos_x(8) + 19 + (6 * promo_cur);
        pos.Y = board_pos_y(6);
        SetConsoleCursorPosition(hConsole, pos);

        if(turn == 1) set_color(txt_color_white, back_color_yellow);
        else set_color(txt_color_black, back_color_yellow);
        printf(" %c ", pieces[promo_cur]);

        move_cursor_in_promote_window();

        if(key_input == '\r') break;
    }
    
    current_chess_board.piece[y-1][x-1] = pieces[promo_cur];
    current_chess_board.info[y-1][x-1] = turn;

    where_is_cursor = GAME_BOARD;
    print_game_board_frame();
    print_promote_window();
}

void move_cursor_in_promote_window()
{
    key_input = getch();
    
    switch (key_input)
    {
        case 'a': case 'A':
            if(promo_cur == 0)
            {
                promo_cur = 3;
                break;
            } else {
                promo_cur--;
                break;
            }
        case 'd': case 'D':
            if(promo_cur == 3)
            {
                promo_cur = 0;
                break;
            } else {
                promo_cur++;
                break;
            }
        case '\r':
            break;
        default:
            break;
    }
}