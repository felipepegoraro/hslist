#include "../UI.h"
#include "./ui_search.h"
#include <form.h>
#include <string.h>
#include "../types.h"

void ui_window_search(HashTable *hs)
{
  ui_clear_and_refresh();

  WINDOW *searchWin = newwin(0, 0, 0, 0);

  current_window = searchWin;
  box(searchWin, 0, 0);

  mvwprintw(searchWin, 2, 2, "Buscar Contato");

  ui_window_search_helper(searchWin, hs);

  wrefresh(searchWin);
  curs_set(1);

  ui_start(hs);
}

void ui_window_search_helper(WINDOW *win, HashTable *hs)
{
  FIELD *field[2];
  field[0] = new_field(1, MAX_NAME_SIZE + 1, 5, 2, 0, 0);
  field[1] = NULL;

  set_field_back(field[0], A_UNDERLINE);
  field_opts_off(field[0], O_AUTOSKIP);

  FORM *form = new_form(field);
  post_form(form);
  refresh();

  char name[MAX_NAME_SIZE];
  int ch;

  curs_set(1);
  move(5,2);
  do {
    mvprintw(2, 2, "Buscar Contato");
    mvprintw(3, 2, "Pressione F2 para voltar");

    switch (ch)
    {
      case KEY_F(2):
        unpost_form(form);
        free_form(form);
        free_field(field[0]);
        delwin(win);
        refresh();
        return;

      case 10:
        form_driver(form, REQ_NEXT_FIELD);
        form_driver(form, REQ_NEXT_FIELD);
        strcpy(name, trim_whitespace(field_buffer(field[0], 0)));

        Entry *result = hs_search(hs, name);

        werase(win);

        if (result != NULL) {
          Contact *found_contact = (Contact *)result->value;
          mvprintw(5, 2, "Usuário encontrado: %s (%s), %s", found_contact->name, found_contact->address, found_contact->phone);
        } else {
          mvwprintw(win, 7, 2, "Usuário %s não encontrado.", name);
        }

        ui_clear_fields(form, (FORM **)field);
        // wgetch(win);
        wrefresh(win);

        break;

      default:
        form_driver(form, ch);
        break;
    }
  } while ((ch = getch()) != KEY_F(2));

  curs_set(0);

  unpost_form(form);
  free_form(form);
  free_field(field[0]);
  delwin(win);
  refresh();
}
