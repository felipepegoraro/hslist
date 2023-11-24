#include "./file_io.h"
#include <stdbool.h>
#include "./hash_table.h"

#define MAX_LINE_SIZE (MAX_NAME_SIZE + MAX_ADDRESS_SIZE + MAX_PHONE_SIZE + 4)

void io_if_error(FILE *file)
{
  if (file == NULL){
    char msg[100];
    sprintf(msg, "nao foi possivel ler/abrir arquivo %s", CONTACT_LIST_FILENAME);
    perror(msg);
  }
}

FILE *io_open_file(const char *filename)
{
  FILE *fp = fopen(filename, "r+");
  io_if_error(fp);
  return fp;
}

bool io_file_is_empty(FILE *filename)
{
  io_if_error(filename);
  fseek(filename, 0, SEEK_END);
  long length = ftell(filename);
  return length == 0;
}


void io_free_file(FILE *file)
{
  if (file != NULL)
    fclose(file);
}

void io_read_from_csv(FILE *file, Contact *to, size_t max_contacts, int *count)
{
  if (count == NULL)
    return;
  char line[MAX_LINE_SIZE];

  size_t contact_count = 0;
  while (fgets(line, MAX_LINE_SIZE, file) != NULL && contact_count < max_contacts)
  {
    line[strcspn(line, "\n")] = '\0';

    char *token = strtok(line, ";");
    if (token == NULL) continue;

    to[contact_count].name = strdup(token);

    token = strtok(NULL, ";");
    if (token == NULL){
        free((void *)to[contact_count].name);
        continue;
    }
    to[contact_count].address = strdup(token);

    token = strtok(NULL, ";");
    if (token == NULL) {
        free((void *)to[contact_count].name);
        free((void *)to[contact_count].address);
        continue;
    }
    to[contact_count].phone = strdup(token);

    contact_count++;
    *count = *count + 1;
  }
}

void io_write_to_csv(FILE *file, const HashTable *from)
{
  if (from->length == 0) return;
  size_t size = from->size;

  for (size_t i = 0; i < size; i++){
    Entry *current = from->buckets[i];

    while (current != NULL)
    {
      Contact *ct = (Contact*) current->value;
      fprintf(file, "%s;%s;%s\n", ct->name, ct->address, ct->phone);
      current = current->next;
    }
  }
}


void io_clean_file(FILE *file)
{
  if (file != NULL){
    fclose(file);
    file = freopen(CONTACT_LIST_FILENAME, "w", file);
  }
}
