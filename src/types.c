#include "./types.h"
#include <stdio.h>
#include <ncurses.h>
#include "./UI.h"

Contact_Record create_contact_record(const int id, const Contact *ct)
{
  Contact_Record ctr = {
    id,
    *ct,
    get_current_time()
  };

  return ctr;
}

void print_contact(Contact *contact, WINDOW *listWindow, int idx)
{
  mvwprintw(listWindow, 6+idx, 2, "%s (%s), %s",
            contact->name,
            contact->address,
            contact->phone);
}

time_t get_current_time(void)
{
  return time(NULL);
}
