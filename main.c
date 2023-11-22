#include "./src/UI.h"
#include "./src/types.h"
#include "./src/hash_table.h"
#include <stdio.h>
#include <stdlib.h>

/*
void example(void)
{
  Contact cts[] = {
    {"John Doe", "123 Main St", "555-1234"},
    {"Alice Johnson", "456 Oak Ave", "555-5678"},
    {"Bob Smith", "789 Pine Blvd", "555-9876"},
    {"Eva White", "321 Cedar Ln", "555-5432"},
    {"David Brown", "654 Elm Rd", "555-6789"},
    {"Grace Davis", "987 Birch Dr", "555-2345"},
    {"Michael Lee", "210 Maple Ct", "555-8765"},
    {"Sophia Taylor", "753 Spruce Pl", "555-3456"},
    {"Ryan Clark", "147 Fir Rd", "555-6543"}
  };

  // CRIAR HASH TABLE
  HashTable *hs = hs_create(sizeof(char)*MAX_KEY_SIZE, sizeof(struct contact_record), 1024);
  size_t cts_len = sizeof(cts) / sizeof(cts[0]);

  // INSERIR VARIOS CONTATOS
  for (size_t i=0; i < cts_len; i++)
    hs_insert(hs, (char*)cts[i].name, (Contact*)&cts[i]);

  // LISTAR CONTATOS
  hs_map(hs, (void (*)(void *, size_t)) print_contact, sizeof(Contact));
  // printf("%zu\n", hs->length);

  // REMOVER CONTATOS
  // printf("\n\n removendo Bob Smith \n\n");
  hs_delete(hs, "Bob Smith");

  // LISTAR CONTATOS
  hs_map(hs, (void (*)(void *, size_t)) print_contact, sizeof(Contact));

  // EXIBIR QUANTIDADE DE CONTATOS
  // printf("%zu\n", hs->length);

  // printf("\n\n removendo Lorem Ipsum \n\n");
  hs_delete(hs, "Lorem Ipsum");
  hs_map(hs, (void (*)(void *, size_t)) print_contact, sizeof(Contact));
  // printf("%zu\n", hs->length);

  hs_free(hs);
}
*/

int main(void)
{
  // example();
  Contact cts[] = {
    {"John Doe", "123 Main St", "555-1234"},
    {"Alice Johnson", "456 Oak Ave", "555-5678"},
    {"Bob Smith", "789 Pine Blvd", "555-9876"},
    {"Eva White", "321 Cedar Ln", "555-5432"},
    {"David Brown", "654 Elm Rd", "555-6789"},
    {"Grace Davis", "987 Birch Dr", "555-2345"},
    {"Michael Lee", "210 Maple Ct", "555-8765"},
    {"Sophia Taylor", "753 Spruce Pl", "555-3456"},
    {"Ryan Clark", "147 Fir Rd", "555-6543"}
  };

  HashTable *hs = hs_create(sizeof(struct contact), 1024);
  size_t cts_len = sizeof(cts) / sizeof(cts[0]);

  for (size_t i=0; i < cts_len; i++)
    hs_insert(hs, (char*)cts[i].name, (Contact*)&cts[i]);

  ui_start(hs);
  // hs_map(hs, (void (*)(void *, size_t)) print_contact, sizeof(Contact));

  return 0;
}
