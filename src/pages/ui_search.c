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

  ui_window_search_helper(searchWin, hs);

  wrefresh(searchWin);
  curs_set(1);

  ui_start(hs);
}

void ui_window_search_helper(WINDOW *win, HashTable *hs)
{
  size_t num_of_fields = 2;
  FIELD *fields[num_of_fields];
  fields[0] = new_field(1, MAX_NAME_SIZE + 1, 5, 2, 0, 0);
  fields[1] = NULL;

  set_field_back(fields[0], A_UNDERLINE);
  field_opts_off(fields[0], O_AUTOSKIP);

  FORM *form = new_form(fields);
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
        ui_clean_and_free_forms(win, form, fields, num_of_fields-1);
        return;

      case 10:
        form_driver(form, REQ_NEXT_FIELD);
        form_driver(form, REQ_NEXT_FIELD);
        strcpy(name, trim_whitespace(field_buffer(fields[0], 0)));

        if (strlen(name) == 0)
          mvprintw(2, 17, "[Preencha o campo contato!]");

        Entry *result = hs_search(hs, name);

        werase(win);

        if (result != NULL){
          Contact *found_contact = (Contact *)result->value;
          mvprintw(7, 2, "Usuário encontrado: %s (%s), %s",
              found_contact->name,
              found_contact->address,
              found_contact->phone);
          
          wclrtoeol(stdscr);
        }
        else mvwprintw(win, 7, 2, "Usuário %s não encontrado.", name);

        ui_clear_fields(form, fields);
        wrefresh(win);
        break;

      default:
        form_driver(form, ch);
        break;
    }
  } while ((ch = getch()) != KEY_F(2));

  curs_set(0);

  ui_clean_and_free_forms(win, form, fields, num_of_fields-1);
  refresh();
}
