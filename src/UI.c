#include <ncurses.h>
#include <string.h>
#include "./UI.h"
#include "./hash_table.h"
#include "./pages/ui_add.h"
#include "./pages/ui_list.h"
#include "./pages/ui_search.h"
#include "./pages/ui_remove.h"
#include <ctype.h>

void ui_clear_and_refresh(void)
{
  clear();
  refresh();
}

void ui_start(HashTable *hs)
{
  initscr();

  noecho();
  curs_set(0);

  keypad(stdscr, true);
  current_window = newwin(0,0,0,0);
  box(current_window, 0, 0);

  getmaxyx(stdscr, height, width);


  int selected_menu = ui_menu_select();
  switch (selected_menu)
  {
    case ADD_WIN: ui_window_add(hs); break;  
    case REMOVE_WIN: ui_window_remove(hs); break;
    case SEARCH_WIN: ui_window_search(hs); break;
    case LIST_WIN: ui_window_list(hs); break;

    default: break;
  }

  wrefresh(current_window);
  wgetch(current_window);
  endwin();
}


int ui_menu_select(void)
{
  WINDOW *main_window = newwin(0,0,0,0);
  current_window = main_window;
  box(main_window, 0, 0);
  ui_print_logo(main_window, height, width);

  int highlight = 0;
  int selected = 0;

  while (1)
  {
    for (int i = 0; i < 4; i++)
    {
      if (i == highlight) wattron(main_window, A_REVERSE);

      mvwprintw(
        main_window,
        height/2.2+i + 1,
        width/2 - strlen(main_menu_options[0] - 10),
        "%d. %s", i+1, main_menu_options[i]
      );

      wattroff(main_window, A_REVERSE);
    }

    selected = wgetch(main_window);

    switch (selected)
    {
      case 'A': highlight = (highlight == 0) ? 3 : highlight - 1; break;
      case 'B': highlight = (highlight == 3) ? 0 : highlight + 1; break;

      case 49:
      case 50:
      case 51:
      case 52:
        highlight = selected-49;
        break;

      case 10:
        endwin();

        switch (highlight)
        {
          case 0:  return ADD_WIN;
          case 1:  return REMOVE_WIN;
          case 2:  return SEARCH_WIN;
          case 3:  return LIST_WIN;
        }

      wrefresh(main_window);
    }
  }
}

void ui_print_logo(WINDOW *win, int height, int width)
{
  const char *text = logo;
  const char *start = text;
  int text_height = 0;

  while (*start != '\0')
  {
    if (*start == '\n') text_height++;
    start++;
  }
  
  for (int i = 0; i < text_height; i++)
  {
    int length;
    const char *newline_position = strchr(text, '\n');

    if (newline_position != NULL) length = newline_position - text;
    else length = strlen(text);

    int y, x;

    const int ymax = (height - 1) / 2 - (text_height*3) + i;
    y = (ymax <= height) ? ymax + text_height+2 : ymax;
    x = (width - length) / 2;

    wmove(win, y, x);
    wprintw(win, "%.*s", length, text);
    refresh();

    text = newline_position != NULL ? newline_position + 1 : text + length;
  }
}

void ui_clear_fields(FORM *form, FIELD *fields[])
{
  for (int i = 0; fields[i] != NULL; ++i)
  {
    set_field_buffer(fields[i], 0, "");  // Limpar o buffer do campo
    form_driver(form, REQ_NEXT_FIELD);
  }
}

char *trim_whitespace(char *str)
{
  char *end;
  while (isspace((unsigned char)*str)) str++;
  if (*str == 0) return str;
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end)) end--;
  end[1] = '\0';
  return str;
}
