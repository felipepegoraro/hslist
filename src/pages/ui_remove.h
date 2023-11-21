#ifndef UI_REMOVE_PAGE
#define UI_REMOVE_PAGE

#include "../hash_table.h"

void ui_window_remove(HashTable *hs);
void ui_window_remove_helper(WINDOW *win, HashTable *hs);

#endif // !UI_REMOVE_PAGE
