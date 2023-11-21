#ifndef UI_ADD_PAGE
#define UI_ADD_PAGE

#include "../hash_table.h"
#include <ncurses.h>

void ui_window_add(HashTable *hs);
void ui_window_add_helper(WINDOW *win, HashTable *hs);

#endif // !UI_ADD_PAGE
