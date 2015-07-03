#!/usr/local/bin/perl
#
# Print out which lines in a set of files are too long
#

$line = 1;
$currFile = $ARGV;
while(<>){
  if($ARGV ne $currFile){
	$line = 1;
	$currFile = $ARGV;
  }
  if(length($_) > 80){
	print "$ARGV:$line\n$_";
  }
  $line++;
}
