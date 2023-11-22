#ifndef UI
#define UI

#include "./hash_table.h"
#include <ncurses.h>
#include <form.h>

static WINDOW *current_window __attribute__((unused));

// typedef void (*fn)(void);

typedef struct point {
  int y;
  int x;
} Point;

void ui_clear_and_refresh(void);
void ui_start(HashTable *);
void ui_print_logo(WINDOW *win, int height, int width);


#define    ADD_WIN 1
#define REMOVE_WIN 2
#define SEARCH_WIN 3
#define   LIST_WIN 4

int ui_menu_select(void);


static const char *logo __attribute__((unused)) =
  "  _         _ _     _   \n"
  " | |       | (_)   | |  \n"
  " | |__  ___| |_ ___| |_ \n"
  " | '_ \\/ __| | / __| __|\n"
  " | | | \\__ \\ | \\__ \\ |_ \n"
  " |_| |_|___/_|_|___/\\__|\n"
;

static int __attribute__((unused)) width;
static int __attribute__((unused)) height;

static const char *main_menu_options[] __attribute__((unused)) = {
  "adicionar", "remover", "buscar", "listar"
};

void ui_clear_fields(FORM *form, FIELD *fields[]);
char *trim_whitespace(char *);

#endif // !UI
