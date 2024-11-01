#include "all_headers.h"

int where_is_cursor = GAME_BOARD;

void goto_main_menu_page()
{
    while(1)
    {
        clear_console();
        print_main_menu_frame();

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { 0, board_pos_y(1) };
        SetConsoleCursorPosition(hConsole, pos);

        switch (main_menu_cursor_pos)
        {
            case 1:
                set_color(txt_color_green, back_color_white);
                printf("\t>> New Game <<\n\n");
                set_color(txt_color_black, back_color_grey);
                printf("\t   Continue Game   \n\n");
                printf("\t   Exit   ");
                break;
            case 2:
                set_color(txt_color_black, back_color_grey);
                printf("\t   New Game   \n\n");
                set_color(txt_color_green, back_color_white);
                printf("\t>> Continue Game <<\n\n");
                set_color(txt_color_black, back_color_grey);
                printf("\t   Exit   ");
                break;
            case 3:
                set_color(txt_color_black, back_color_grey);
                printf("\t   New Game   \n\n");
                printf("\t   Continue Game   \n\n");
                set_color(txt_color_green, back_color_white);
                printf("\t>> Exit <<");
                break;
            default:
                break;
        }

        move_cursor_in_main_menu();

        if(key_input == '\r')
        {
            break;
        }
    }
}

void goto_game_page()
{
    clear_console();
    print_game_board_frame();
    print_side_info();
    print_promote_window();

    CURSOR_POS selected_piece_pos;

    while(1)
    {
        while(1)
        {
            print_turn();
            print_current_pieces();
            print_guide_line_on_the_board();
            print_cursor_on_the_board();
            move_cursor_in_game_board();

            if(key_input == 'm' || key_input == 'M')
            {
                return;
            }

            if(key_input == '\r' && is_my_piece_current() == 1 && count_moveable_pos() != 0)
            {
                selected_piece_pos = game_board_cursor_pos;
                break;
            }
        }
        
        while(1)
        {
            print_current_pieces();
            print_guide_line_from_moveable_pos();
            print_cursor_on_the_board();
            move_cursor_in_game_board();

            if(key_input == '\r' && is_my_piece_current() != 1)
            {
                if(moveable_pos[game_board_cursor_pos.y-1][game_board_cursor_pos.x-1] == 1)
                {
                    move_piece(selected_piece_pos, game_board_cursor_pos);

                    if(is_game_over() == 1)
                    {
                        goto_game_over_page();
                        return;
                    }
                    check_pawn();
                    turn_change();
                    save_game_data();
                    break;
                }
                else
                {
                    break;
                }
            }
            else if(key_input == '\r' && is_my_piece_current() == 1)
            {
                print_guide_line_on_the_board();
                if(count_moveable_pos() != 0)
                {
                    selected_piece_pos = game_board_cursor_pos;
                    continue;
                }
                else if(count_moveable_pos() == 0)
                {
                    break;
                }
                
            }
        }
    }
}

void goto_file_error_page()
{
    clear_console();

    set_color(txt_color_red, back_color_black);
    printf("\n\tFile Error\n\n");

    reset_color();
    printf("\tThere is no saved game data.\n\n");
    
    printf("\tPress any key to continue...");
    getch();
}

void goto_game_over_page()
{
    clear_console();
    is_on_game_now = 0;

    save_game_data();
    
    set_color(txt_color_red, back_color_black);
    printf("\n\tGame Over\n\n");

    reset_color();
    printf("\tThe Winner Is ");

    if(turn == 1)
    {
        set_color(txt_color_white, back_color_green);
        printf(" White ");
    }
    else if(turn == 2)
    {
        set_color(txt_color_black, back_color_green);
        printf(" Black ");
    }
    reset_color();
    printf(" !!!\n\n");

    printf("\tPress any key to continue...");
    getch();
}

void goto_exit_page()
{
    set_color(txt_color_red, back_color_black);
    printf("\n\n\tExit\n\n");

    reset_color();
    printf("\tThank you for playing my ");

    set_color(txt_color_black, back_color_green);
    printf(" Chess Game ");

    reset_color();
    printf(" !!!\n\n");

    printf("\tPress any key to exit...\n\n");

    set_color(txt_color_grey, back_color_black);
}