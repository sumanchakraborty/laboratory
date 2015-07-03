package xpert_utility;

use warnings;
use Time::localtime;
use Date::Calc qw (Today);
use xpert_syntax;
use Exporter;
use base 'Exporter';

our @EXPORT = qw( date copyright );

sub date
{
  my $FILE = $_[0];
  ($Y, $M, $D) = Today();

  print $FILE $NL.$TAB;
  print $FILE "Date ".$D."/".$M."/".$Y;
  print $FILE $NL;
}

sub copyright
{
  my $FILE = $_[0];

  print $FILE $NL.$TAB;
  print $FILE "Copyright (c) Ixia ", localtime->year()+1900;
  print $FILE $NL.$TAB;
  print $FILE "All rights reserved.";
  print $FILE $NL;

}
