
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct {
  char *name;
} Person;
 
void print_name(Person *pers) {
  puts(pers->name);
}
 
int main(int argc, char **argv) {
  GSList *list = NULL;
  Person *pers = NULL;
 
  pers = g_new(Person, 1);
  pers->name = "Daniel";
 
  list = g_slist_append(list, pers);
  
  pers = g_new(Person, 1);
  pers->name = "Bernd";
 
  list = g_slist_append(list, pers);
 
  g_slist_foreach(list, (GFunc)print_name, NULL);
 
  g_slist_foreach(list, (GFunc)g_free, NULL);
  g_slist_free(list);
 
  return EXIT_SUCCESS;
}

