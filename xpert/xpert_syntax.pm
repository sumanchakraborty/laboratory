package xpert_syntax;

use strict;
use warnings;
use Exporter;
use base 'Exporter';

our @EXPORT = qw( $DEFINE    $ENUM
                  $STRUCT    $TYPEDEF
                  $NL        $USCORE
                  $COMMA     $SPACE
                  $TAB       $COLON
                  $SEMICOLON $OBRACE_1
                  $OBRACE_2  $OBRACE_3
                  $CBRACE_1  $CBRACE_2
                  $CBRACE_3  $IFNDEF
                  $ENDIF     $COMMENT_START
                  $COMMENT_STOP $DNL $INCLUDE);

# keyword -----------

our $INCLUDE      = "#include";
our $DEFINE       = "#define";
our $IFNDEF       = "#ifndef";
our $ENDIF        = "#endif";
our $ENUM         = "enum";
our $STRUCT       = "struct";
our $TYPEDEF      = "typedef";

# charecter ---------

our $NL           = "\n";
our $USCORE       = "_";
our $COMMA        = ",";
our $SPACE        = " ";
our $COLON        = ":";
our $SEMICOLON    = ";";

# brace -------------

our $OBRACE_1 = "(";
our $OBRACE_2 = "{";
our $OBRACE_3 = "[";
our $CBRACE_1 = ")";
our $CBRACE_2 = "}";
our $CBRACE_3 = "]";

# compund -------------
our $DNL           = $NL.$NL;
our $TAB           = $SPACE.$SPACE;
our $COMMENT_START = "/*";
our $COMMENT_STOP  = "*/";

