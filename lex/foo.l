
/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
%}

ALPHA    [a-zA-Z_]
DIGIT    [0-9]
ID       [a-z][a-z0-9]*
HEXDIGIT [0-9a-fA-F]

%%

{DIGIT}+  {
                // number starts with 0
                printf( "A number: %s (%d)\n", yytext, strtol(yytext, 0, 10));
                //yylval->variable = sp->allocateString(yytext,yyleng);
                //return token::STRING;
            }

{DIGIT}+"."{DIGIT}*        {
            printf( "A float: %s (%g)\n", yytext,
                    atof( yytext ) );
            }

"."{DIGIT}+        {
            printf( "A small float: %s (%g)\n", yytext,
                    atof( yytext ) );
            }

(0[xX]{HEXDIGIT}+)  {
        // standard hex integer: e.g. 0xAbcDe0123
        //  or just a digit.
        printf( "A hex: %s\n", yytext );
    }

if|then|begin|end|procedure|function        {
            printf( "A keyword: %s\n", yytext );
            }

{ID}        printf( "An identifier: %s\n", yytext );

"+"|"-"|"*"|"/"   printf( "An operator: %s\n", yytext );

"{"[^}\n]*"}"     /* eat up one-line comments */

[ \t\n]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );

%%

main( argc, argv )
int argc;
char **argv;
{
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    yylex();
}

yywrap()
{
    return 1;
}
