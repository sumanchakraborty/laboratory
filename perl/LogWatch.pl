#! /usr/bin/perl

our $num = 0;
our $count = 0;
our $status = 0;

if (@ARGV != 2) {
  print"Usage: LogWatch.pl <INPUT_FILE> <OUTPUT_FILE>\n";
  exit 0;
}

$in  = @ARGV[0];
$out  = @ARGV[1];

open(infile, "$in") || die "Can't open :$in";
open(outfile, ">>$out") || die "Can't open :$out";

print "#########################\n";
print "The input file is \"$in\"\n";
print "The output file is \"$out\"\n";
print "#########################\n";

while(1){
  system ("cat $in | grep \"<< \" > $out");
  system ("tail -n 1 $out");
  sleep 5;
}

close infile;
close outfile;
