#include "./file_io.h"
#include <stdbool.h>
#include "./hash_table.h"

#define MAX_LINE_SIZE (MAX_NAME_SIZE + MAX_ADDRESS_SIZE + MAX_PHONE_SIZE + 4)

bool io_if_error(FILE *file)
{
  bool ret = true;

  if (file == NULL){
    char msg[100];
    sprintf(msg, "nao foi possivel ler/abrir arquivo %s", CONTACT_LIST_FILENAME);
    perror(msg);
    ret = false;
  }

  return ret;
}

FILE *io_open_file(const char *filename, const char mode[2])
{
  FILE *fp = fopen(filename, mode);
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
  if (file != NULL){
    fclose(file);
  }
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

    strcpy(to[contact_count].name, token);

    token = strtok(NULL, ";");
    if (token == NULL){
        free((void *)to[contact_count].name);
        continue;
    }
    strcpy(to[contact_count].address, token);

    token = strtok(NULL, ";");
    if (token == NULL) {
        free((void *)to[contact_count].name);
        free((void *)to[contact_count].address);
        continue;
    }
    strcpy(to[contact_count].phone, token);

    contact_count++;
    *count = *count + 1;
  }

  if (!io_if_error(file)){
    for (size_t i = 0; i < contact_count; i++){
      free((void *)to[i].name);
      free((void *)to[i].address);
      free((void *)to[i].phone);
    }
    *count = 0;
  }}

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


void io_clean_file(FILE *file) {
  if (file != NULL) {
    if (fclose(file) != 0) {
      perror("Erro ao fechar o arquivo");
      exit(EXIT_FAILURE);
    }
    file = fopen(CONTACT_LIST_FILENAME, "w");
    if(!io_if_error(file)){
      mvprintw(10, 2, "erro ao abrir arquivo");
    }
  }
}
