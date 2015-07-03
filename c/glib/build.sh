
#!/bin/sh

rm -rf person
gcc `pkg-config --cflags glib-2.0` -o person person.c `pkg-config --libs glib-2.0`

./person

