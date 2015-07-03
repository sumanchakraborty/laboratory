#! /usr/bin/perl

our $count = 0;
our $status = 0;

if (@ARGV != 3) {
  print"Usage: SearchTestNumberThroughKeyword.pl <KEYWORD> <INPUT_FILE> <OUTPUT_FILE>\n";
  exit 0;
}

$key  = @ARGV[0];
$in  = @ARGV[1];
$out = @ARGV[2];

open(infile,"$in") || die "Can't open input.txt:$1";
open(outfile,">$out") || die "Can't open input.txt:$1";

# get each line of the file in the array
  @array = <infile>;
  $size = @array;

  for($index = 0; $index <= $size; $index++) {
    chop(@array[$index]);
    $line = @array[$index];

# print line number if keyword matches
    if ($line =~ /$key/){
#    if ($line =~ /HTTP_DUT_CONF_AS_ORIGIN_SERVER.*TRUE .*$/){
#    if ($line =~ /HTTP_DUT_CONF_AS_ORIGIN_SERVER.*TRUE$/){
#    if ($line =~ /HTTP_DUT_CONF_AS_PROXY_SERVER.*TRUE .*$/){
#    if ($line =~ /HTTP_DUT_CONF_AS_PROXY_SERVER.*TRUE$/){
      $count++;
      print outfile "$line\n";
    }
  }

# print the total test number
  print "For pattern $key\n";
  print "The total occurence is $count\n";

close infile;
close outfile;
