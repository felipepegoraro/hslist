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

  mvwprintw(removerwin, 2, 2, "Remover Contatos");

  curs_set(1);
  ui_window_remove_helper(removerwin, hs);
  curs_set(0);

  wrefresh(removerwin);
  ui_start(hs);
}

void ui_window_remove_helper(WINDOW *win, HashTable *hs)
{
  FIELD *fields[2];
  fields[0] = new_field(1, MAX_NAME_SIZE, 2, 2, 0, 0);
  fields[1] = NULL;

  set_field_back(fields[0], A_UNDERLINE); field_opts_off(fields[0], O_AUTOSKIP);

  FORM *form = new_form(fields);
  post_form(form);
  refresh();

  char name[MAX_NAME_SIZE];

  int ch;
  mvprintw(2, 2, "Pressione F2 para voltar");

  while ((ch = getch()) != KEY_F(2))
  {
    switch (ch)
    {
      case KEY_F(2):
        unpost_form(form);
        free_form(form);
        free_field(fields[0]);
        free_field(fields[1]);
        delwin(win);
        refresh();
        return;

        case 10:
          form_driver(form, REQ_NEXT_FIELD);
          form_driver(form, REQ_PREV_FIELD);

          strcpy(name, trim_whitespace(field_buffer(fields[0], 0)));

          if (strlen(name) == 0)
          {
            ui_clear_fields(form, (FORM**)fields);
            mvprintw(10, 2, "Preencha o inputs nome");
            break;
          }

          hs_delete(hs, strdup(name));
          mvprintw(10, 2, "Contato Removido!");

          ui_clear_fields(form, (FORM**)fields);

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

  unpost_form(form);
  free_form(form);
  free_field(fields[0]);
  free_field(fields[1]);
  delwin(win);
  refresh();
}

