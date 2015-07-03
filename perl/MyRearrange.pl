#! /usr/bin/perl

#! /usr/bin/perl

if (@ARGV != 2) {
  print"Usage: Rearrange.pl <INPUT_FILE> <OUTPUT_FILE>\n";
  exit 0;
}

$in =  @ARGV[0];
$out = @ARGV[1];

my $refFound = 0;
my $page = "";

open(INFILE, "$in") || die "Can't open <INPUT_FILE>";
open(OUTFILE, ">$out") || die "Can't open <OUTPUT_FILE>";

while(<INFILE>){

  if($refFound){
    $page = m/Page/;
    print("$page");
    $refFound = 0;
  }

  if(/TEST_REFERENCE/){
    $refFound = 1;
  }
}
