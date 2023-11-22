#include "./ui_add.h"
#include "../hash_table.h"
#include "../UI.h"
#include <ncurses.h>
#include <form.h>
#include <string.h>
#include "../types.h"
#include <stdlib.h>

void ui_window_add(HashTable *hs)
{
  ui_clear_and_refresh();

  WINDOW *adicionarWin = newwin(0, 0, 0, 0);
  current_window = adicionarWin;
  box(adicionarWin, 0, 0);

  curs_set(1);
  ui_window_add_helper(adicionarWin, hs);
  curs_set(0);

  wrefresh(adicionarWin);
  ui_start(hs);
}

void ui_window_add_helper(WINDOW *win, HashTable *hs)
{
  FIELD *fields[4];
  fields[0] = new_field(1, MAX_NAME_SIZE, 5, 2, 0, 0);
  fields[1] = new_field(1, MAX_ADDRESS_SIZE, 7, 2, 0, 0);
  fields[2] = new_field(1, MAX_PHONE_SIZE, 9, 2, 0, 0);
  fields[3] = NULL;

  set_field_back(fields[0], A_UNDERLINE);
  field_opts_off(fields[0], O_AUTOSKIP);
  set_field_back(fields[1], A_UNDERLINE);
  field_opts_off(fields[1], O_AUTOSKIP);
  set_field_back(fields[2], A_UNDERLINE);
  field_opts_off(fields[2], O_AUTOSKIP);

  FORM *form = new_form(fields);
  post_form(form);
  refresh();

  char nome[MAX_NAME_SIZE], endereco[MAX_ADDRESS_SIZE], telefone[MAX_PHONE_SIZE];

  int ch;
  mvprintw(2, 2, "Adicionar Contatos");
  mvprintw(3, 2, "Pressione F2 para voltar");
  move(5, 2);

  while ((ch = getch()) != KEY_F(2))
  {
    switch (ch)
    {
    case KEY_F(2):
        unpost_form(form);
        free_form(form);
        free_field(fields[0]);
        free_field(fields[1]);
        free_field(fields[2]);
        delwin(win);
        refresh();
        return;

    case 10:
        form_driver(form, REQ_NEXT_FIELD);
        form_driver(form, REQ_PREV_FIELD);

        strcpy(nome, trim_whitespace(field_buffer(fields[0], 0)));
        strcpy(endereco, trim_whitespace(field_buffer(fields[1], 0)));
        strcpy(telefone, trim_whitespace(field_buffer(fields[2], 0)));

        if (strlen(nome) == 0 || strlen(endereco) == 0 || strlen(telefone) == 0)
        {
          ui_clear_fields(form, fields);
          mvprintw(2, 21, "[Preencha todos inputs...]");
          move(5, 2);
          refresh();
          break;
        }

        Contact new_contact = {
          .name = strdup(nome),
          .address = strdup(endereco),
          .phone = strdup(telefone),
        };

        hs_insert(hs, (char*)new_contact.name, &new_contact);

        mvprintw(12, 2, "Contato Adicionado!");
        mvprintw(14, 2, "| Nome: %s", nome);
        mvprintw(15, 2, "| Endereco: %s", endereco);
        mvprintw(16, 2, "| Telefone: %s", telefone);

        ui_clear_fields(form, fields);
        // free((char*)new_contact.name);
        // free((char*)new_contact.address);
        // free((char*)new_contact.phone);

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

  unpost_form(form);
  free_form(form);
  free_field(fields[0]);
  free_field(fields[1]);
  free_field(fields[2]);
  delwin(win);
  refresh();
}

