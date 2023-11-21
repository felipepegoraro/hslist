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
  const char *name = contact->name;
  const char *address = contact->address;
  const char *phone = contact->phone;

  mvwprintw(listWindow, 6+idx, 2, "%s (%s), %s", name, address, phone);
}

time_t get_current_time(void)
{
  return time(NULL);
}
