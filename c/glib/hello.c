
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

void display(char *string) {
	printf("The item is '%s'\n", string);
}

int main(int argc, char** argv) {
	GList* list = NULL;
	list = g_list_append(list, "Hello, ");
	list = g_list_append(list, "Suman Chakraborty !");
	g_list_foreach(list, (GFunc)display, NULL);
	return 0;
}

