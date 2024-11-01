#include "all_headers.h"

void clear_console()
{
    reset_color();
    system("cls");
}

void first_console_setting() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;

    ConsoleCursor.bVisible = FALSE; 
    ConsoleCursor.dwSize = 1;       

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void print_game_board_frame()
{
    if(where_is_cursor == GAME_BOARD)
    {
        set_color(FRAME_ON_COLOR, back_color_black);
    }
    else if (where_is_cursor == SIDE_MENU)
    {
        set_color(txt_color_grey, back_color_black);
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos = { pos_x(4), 2 };
    SetConsoleCursorPosition(hConsole, pos);
    printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");

    int i;
    for(i=0; i<15; i++)
    {
        pos.X = board_pos_x(1)-2;
        pos.Y = 3+i;
        SetConsoleCursorPosition(hConsole, pos);
        printf("弛");

        pos.X = board_pos_x(8)+4;
        pos.Y = 3+i;
        SetConsoleCursorPosition(hConsole, pos);
        printf("弛");
    }
    
    pos.X = pos_x(4);
    pos.Y = board_pos_y(8)+1;
    SetConsoleCursorPosition(hConsole, pos);
    printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");

    reset_color();
}

void print_side_info()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { board_pos_x(8)+10, board_pos_y(1)-1};
    SetConsoleCursorPosition(hConsole, pos);

    set_color(txt_color_grey, back_color_black);
    printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");

    int i;
    for(i=0;i<3;i++)
    {
        pos.X = board_pos_x(8)+10;
        pos.Y = board_pos_y(1)+i;
        SetConsoleCursorPosition(hConsole, pos);
        printf("弛");
    }

    for(i=0;i<3;i++)
    {
        pos.X = board_pos_x(8)+10+1+37+2;
        pos.Y = board_pos_y(1)+i;
        SetConsoleCursorPosition(hConsole, pos);
        printf("弛");
    }

    pos.X = board_pos_x(8)+10;
    pos.Y = board_pos_y(1)+3;
    SetConsoleCursorPosition(hConsole, pos);
    printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");

    pos.X = board_pos_x(8)+12;
    pos.Y = board_pos_y(1);
    SetConsoleCursorPosition(hConsole, pos);

    reset_color();
    printf("Press 'm' to return to the main menu.");
}

void print_current_pieces()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    set_color(txt_color_black, PIECE_BACK_COLOR);

    int a,b;
    for(a=1; a<=8; a++)
    {
        for(b=1; b<=8; b++)
        {
            COORD pos = { board_pos_x(b), board_pos_y(a) };
            SetConsoleCursorPosition(hConsole, pos);
            
            if(current_chess_board.info[a-1][b-1] == 2)
            {
                set_color(txt_color_black, PIECE_BACK_COLOR);
            } 
            else if(current_chess_board.info[a-1][b-1] == 1) 
            {
                set_color(txt_color_white, PIECE_BACK_COLOR);
            }
            else 
            {
                set_color(txt_color_black, BOARD_BACK_COLOR);
            }
            printf(" %c ", current_chess_board.piece[a-1][b-1]);
        }
    }
    reset_color();
}

void print_cursor_on_the_board()
{
    if(is_enemy_current() == 1)
    {
        set_color(txt_color_red, CURSOR_COLOR);
    }
    else if(is_my_piece_current() == 1)
    {
        set_color(txt_color_green, CURSOR_COLOR);
    }
    else if(is_enemy_current() == -1)
    {
        int x = game_board_cursor_pos.x;
        int y = game_board_cursor_pos.y;
        
        if(moveable_pos[y-1][x-1] == 1)
        {
            set_color(txt_color_green, CURSOR_COLOR);
        }
        else
        {
            set_color(txt_color_grey, CURSOR_COLOR);
        }
        
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { board_pos_x(game_board_cursor_pos.x), board_pos_y(game_board_cursor_pos.y) };
    SetConsoleCursorPosition(hConsole, pos);
    
    printf("|%c|", current_chess_board.piece[game_board_cursor_pos.y-1][game_board_cursor_pos.x-1]);
    
    reset_color();
}

int moveable_pos[8][8];

void print_guide_line_on_the_board()
{
    clear_moveable_pos();

    if(current_chess_board.info[game_board_cursor_pos.y-1][game_board_cursor_pos.x-1] == 0)
    {
        return;
    }
    else if (is_enemy_current() == 1)
    {
        return;
    }

    char piece = current_chess_board.piece[game_board_cursor_pos.y-1][game_board_cursor_pos.x-1];

    switch (piece)
    {
    case 'P':
        guide_line_logic_Pawn();
        break;
    case 'R':
        guide_line_logic_Rook();
        break;
    case 'N':
        guide_line_logic_Knight();
        break;
    case 'B':
        guide_line_logic_Bishop();
        break;
    case 'Q':
        guide_line_logic_Queen();
        break;
    case 'K':
        guide_line_logic_King();
        break;
    default:
        break;
    }
    print_guide_line_from_moveable_pos();
}

void print_guide_line_from_moveable_pos()
{
    int a,b;
    for(a=0; a<8; a++)
    for(b=0; b<8; b++)
        if(moveable_pos[a][b] == 1)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD pos = { board_pos_x(b+1), board_pos_y(a+1) };
            SetConsoleCursorPosition(hConsole, pos);
            
            if(is_enemy(b+1,a+1) == 1)
            {
                set_color(txt_color_red, GUIDE_LINE_BACK_COLOR);
                printf("| |");

                if(turn == 1)
                {
                set_color(txt_color_black, GUIDE_LINE_BACK_COLOR);
                }
                else
                {
                set_color(txt_color_white, GUIDE_LINE_BACK_COLOR);
                }

                pos.X++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("%c", current_chess_board.piece[a][b]);
            }
            else
            {
                set_color(txt_color_green, GUIDE_LINE_BACK_COLOR);
                printf("|%c|", current_chess_board.piece[a][b]);
            }
        }
    reset_color();
}

void print_turn()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { board_pos_x(8)+12, board_pos_y(2)};
    SetConsoleCursorPosition(hConsole, pos);

    reset_color();
    printf("Turn: ");

    if(turn == 1)
    {
        set_color(txt_color_white, back_color_green);
        printf(" White ");
    }
    else
    {
        set_color(txt_color_black, back_color_green);
        printf(" Black ");
    }
    reset_color();
}

void print_main_menu_frame()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { 6, 2 };
    SetConsoleCursorPosition(hConsole, pos);

    set_color(FRAME_ON_COLOR, back_color_black);
    printf("忙式式式式式式式式式式式式式式式式式式式式式忖");

    int i;
    for(i=0; i<5; i++)
    {
        pos.X = 6;
        pos.Y = 3+i;
        SetConsoleCursorPosition(hConsole, pos);
        printf("弛");

        pos.X = 6+21+1;
        pos.Y = 3+i;
        SetConsoleCursorPosition(hConsole, pos);
        printf("弛");
    }
    pos.X = 6;
    pos.Y = 3+5;
    SetConsoleCursorPosition(hConsole, pos);
    printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
}

void print_promote_frame()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { board_pos_x(8)+10, board_pos_y(4)-1 };
    SetConsoleCursorPosition(hConsole, pos);

    if(where_is_cursor == SIDE_MENU)
    {
        set_color(FRAME_ON_COLOR, back_color_black);
    }
    else if (where_is_cursor == GAME_BOARD)
    {
        set_color(txt_color_grey, back_color_black);
    }

    printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");

    int i;
    for(i=0;i<5;i++)
    {
        pos.X = board_pos_x(8)+10;
        pos.Y = board_pos_y(4)+i;
        SetConsoleCursorPosition(hConsole, pos);
        printf("弛");
    }

    for(i=0;i<5;i++)
    {
        pos.X = board_pos_x(8)+10+1+37+2;
        pos.Y = board_pos_y(4)+i;
        SetConsoleCursorPosition(hConsole, pos);
        printf("弛");
    }

    pos.X = board_pos_x(8)+10;
    pos.Y = board_pos_y(4)+5;
    SetConsoleCursorPosition(hConsole, pos);
    printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
}

void print_promote_window()
{
    print_promote_frame();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { board_pos_x(8) + 12, board_pos_y(4) };
    SetConsoleCursorPosition(hConsole, pos);

    reset_color();
    printf("[ Promote Pawn Window ]");

    pos.Y += 2;
    SetConsoleCursorPosition(hConsole, pos);

    printf("Promote Your Pawn ( ");

    set_color(txt_color_blue, back_color_yellow);
    printf("|P|");

    reset_color();
    printf(" ) to...");

    char pieces[4] = {'Q', 'R', 'B', 'N'};

    if(turn == 1)   set_color(txt_color_white, back_color_green);
    else            set_color(txt_color_black, back_color_green);
    
    int i;
    for(i=0; i<4; i++)
    {
        pos.X = board_pos_x(8) + 19 + (6 * i);
        pos.Y = board_pos_y(6);
        SetConsoleCursorPosition(hConsole, pos);
        printf(" %c ", pieces[i]);
    }
}