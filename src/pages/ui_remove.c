#include <form.h>
#include <ncurses.h>
#include "./ui_remove.h"
#include "../UI.h"
#include <string.h>

void ui_window_remove(HashTable *hs)
{
  ui_clear_and_refresh();

  WINDOW *removerwin = newwin(0, 0, 0, 0);
  current_window = removerwin;
  box(removerwin, 0, 0);

  curs_set(1);
  ui_window_remove_helper(removerwin, hs);
  curs_set(0);

  refresh();
  delwin(removerwin);
  ui_start(hs);
}

void ui_window_remove_helper(WINDOW *win, HashTable *hs)
{
  size_t num_of_fields = 2;
  FIELD *fields[num_of_fields];
  fields[0] = new_field(1, MAX_NAME_SIZE, 5, 2, 0, 0);
  fields[1] = NULL;

  set_field_back(fields[0], A_UNDERLINE); field_opts_off(fields[0], O_AUTOSKIP);

  FORM *form = new_form(fields);
  post_form(form);
  refresh();

  char name[MAX_NAME_SIZE];

  mvprintw(2, 2, "Remover Contatos");
  mvprintw(3, 2, "Pressione F2 para voltar");
  move(5, 2);

  int ch;
  while ((ch = getch()) != KEY_F(2))
  {
    switch (ch)
    {
      case KEY_F(2):
        ui_clean_and_free_forms(win, form, fields, num_of_fields);
        return;

      case 10:
        form_driver(form, REQ_NEXT_FIELD);
        // form_driver(form, REQ_PREV_FIELD);

        strcpy(name, trim_whitespace(field_buffer(fields[0], 0)));

        if (strlen(name) == 0)
        {
          ui_clear_fields(form, fields);
          mvprintw(2, 19, "[Preencha o inputs nome]");
          move(5, 2);
          refresh();
          break;
        }

        move(7, 0);
        clrtoeol();

        mvprintw(7, 2, hs_delete(hs, name)
          ? "Contato Removido."
          : "Contato nao encontrado!");
        refresh();

        ui_clear_fields(form, fields);

        move(5, 2);
        refresh();
        break;

      case KEY_DOWN:
        form_driver(form, REQ_NEXT_FIELD);
        form_driver(form, REQ_END_LINE);
        break;
      case KEY_UP:
        form_driver(form, REQ_PREV_FIELD);
        form_driver(form, REQ_END_LINE);
        break;
      default:
          form_driver(form, ch);
          break;
    }
  }

  ui_clean_and_free_forms(win, form, fields, num_of_fields);
  unpost_form(form);
}

