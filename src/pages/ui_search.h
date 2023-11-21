#ifndef UI_SEARCH_PAGE
#define UI_SEARCH_PAGE

#include <ncurses.h>
#include "../hash_table.h"

void ui_window_search(HashTable *);
void ui_window_search_helper(WINDOW *, HashTable *);

#endif // !UI_SEARCH_PAGE
