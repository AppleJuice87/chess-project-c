#include "all_headers.h"

int main()
{
    first_console_setting();
    while(1)
    {
        goto_main_menu_page();
        switch (main_menu_cursor_pos)
        {
            case NEW_GAME:
                set_new_game();
                goto_game_page();
                break;
            case CONTINUE_GAME:
                int temp = load_game_data();
                if      (temp == 1) goto_game_page();
                else if (temp == 0) goto_file_error_page();
                break;
            case EXIT:
                clear_console();
                goto_exit_page();
                return 0;
            default:
                break;
        }
    }
}