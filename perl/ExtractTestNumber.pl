#! /usr/bin/perl

our $state = 0;
if (@ARGV != 3) {
  print"Usage: ExtractTestNumber.pl <MODE> <INPUT_FILE> <OUTPUT_FILE>\n";
  exit 0;
}

$mode  = @ARGV[0];
$in  = @ARGV[1];
$out = @ARGV[2];

open(infile,"$in") || die "Can't open input.txt:$1";
open(outfile,">$out") || die "Can't open input.txt:$1";


# short mode
if($mode == 1){
  while(<infile>) {

      # mark if TEST_NUM/SECTION
      # reached
      if (/TEST_NUM/) {
        $state = 1;
      }

      # print if preveious 
      # line is marked as
      # TEST_NUM/SECTION_NUM
      elsif ($state == 1){
        print outfile "$_";
        $state = 0;
      }
  }
}

# long mode
if($mode == 2){
  while(<infile>) {

      # if NEGATIVE then print it
      if(/NEGATIVE/){
        print outfile "$_";
      }

      # mark if TEST_NUM/SECTION
      # reached
      if (/TEST_NUM/ ||
          /SECTION_NUM/) {
        $state = 1;
      }

      # print if preveious 
      # line is marked as
      # TEST_NUM/SECTION_NUM
      elsif ($state == 1){
        print outfile "$_";
        $state = 0;
      }
  }
}


close infile;
close outfile;
