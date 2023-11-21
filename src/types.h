#ifndef CONTACT_TYPES
#define CONTACT_TYPES

#define MAX_KEY_SIZE 256
#define MAX_NAME_SIZE 32
#define MAX_ADDRESS_SIZE 32
#define MAX_PHONE_SIZE 15

#include <ncurses.h>
#include <time.h>

typedef struct contact {
  const char *name;
  const char *address;
  const char *phone;
} Contact;

typedef struct contact_record {
  const int id;
  const Contact contact;
  const time_t added_date;
} Contact_Record;

Contact_Record create_contact_record(const int, const Contact*);
void print_contact(Contact *contact, WINDOW *listWindow, int idx);
time_t get_current_time(void);

#endif // !CONTACT_TYPES
