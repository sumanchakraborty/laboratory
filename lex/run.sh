
rm -rf foo lex.yy.c;

lex foo.l;
gcc lex.yy.c -o foo;

#rm -rf lex.yy.c;

