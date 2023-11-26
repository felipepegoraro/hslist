#include "./src/file_io.h"
#include "./src/UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

HashTable *hs = NULL;
FILE *contact_list = NULL;

void deallocate_everything(FILE *file, HashTable *hs)
{
  io_clean_file(file);
  io_write_to_csv(file, hs);
  io_free_file(file);
  hs_free(hs);
  printf("list->size %zu\n", hs->length);
}

void handle_sigint() 
{
  deallocate_everything(contact_list, hs);
  endwin();
  printf("desalocou memória [2]\n");
  exit(0);
}

int main(int argc, char*argv[])
{
  size_t max_list_size = MAX_HS_SIZE;
  if (argc > 1) max_list_size = atoi(argv[1]);

  signal(SIGINT, handle_sigint);
  hs = hs_create(sizeof(struct contact), max_list_size);

  contact_list = io_open_file(CONTACT_LIST_FILENAME);

  int count = 0;
  Contact cts[MAX_HS_SIZE];
  io_read_from_csv(contact_list, cts, MAX_HS_SIZE, &count);

  for (int i=0; i < count; i++)
    hs_insert(hs, (char*)cts[i].name, (Contact*)&cts[i]);

  ui_start(hs);

  io_write_to_csv(contact_list, hs);

  deallocate_everything(contact_list, hs);
  printf("desalocou memória [1]\n");

  return 0;
}
