#ifndef FILE_IO
#define FILE_IO
#include <stdio.h>
#include "./hash_table.h"

#ifndef CONTACT_LIST_FILENAME
#define CONTACT_LIST_FILENAME "./.hslist_default_file.csv"
#endif

FILE *io_open_file(const char *filename, const char mode[2]);
bool io_if_error(FILE *file);
void io_free_file(FILE *file);
void io_read_from_csv(FILE *file, Contact *to, size_t max_contacts, int *count);
void io_write_to_csv(FILE *file, const HashTable *from);
void io_clean_file(FILE *file);
bool io_file_is_empty(FILE *filename);

#endif // !FILE_IO
