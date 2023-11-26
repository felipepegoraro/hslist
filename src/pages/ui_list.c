#include  "./ui_list.h"
#include "../UI.h"
#include "../types.h"

void ui_window_list(HashTable *hs)
{
  ui_clear_and_refresh();

  WINDOW *listWindow = newwin(0,0,0,0);
  current_window = listWindow;
  box(listWindow, 0, 0);
  mvwprintw(listWindow, 2, 2, "Listar Contatos");

  wmove(listWindow, 5, 2);
  hs_map(hs, print_contact, listWindow);
  mvwprintw(listWindow, 5+2+hs->length, 2, "pressione qualquer tecla para voltar...");
  refresh();
  wgetch(listWindow);
  delwin(listWindow);
  ui_start(hs);
}
