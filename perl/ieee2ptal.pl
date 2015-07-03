#! /usr/bin/perl

#ptal.plx

#use warnings;
#use strict;

if (@ARGV != 1) {
  print"Usage: rfc2ptal.pl <rfc>\n";
  exit 0;
}

for my $arg (@ARGV) {
    $rfc = $arg;
}

my $page_offset = 20;
my $sec_num;
my $sec_header;
my $page_num = 0;
my $curr_page = 0;
my $isInsideTag=0;
my $begintag="\\\$S";
my $endtag="\\\$E";
my $test_desc="";

open(INFILE,"$rfc") or die "Can't open input.txt:$1";

while(<INFILE>)
{
  if ($isInsideTag == 1) {
    if (/(.*)$endtag/) {
      $test_desc = $test_desc . $1;
      print "--------------------------------------------------------------------------------
TEST_NUM 
TEST_DESCRIPTION 
$test_desc
TEST_REFERENCE
IEEE P802.1ag/D7.1 Section $sec_num Page $curr_page '$sec_header'
TEST_METHOD
TEST_CLASSIFICATION
TCF_MUST\n";
      $test_desc ="";
      $isInsideTag=0;
    }
    else {
      $test_desc =$test_desc . $_;
    }
  }
  elsif (/^(((\d)+)(\.(\d)*)*)\s+[a-zA-Z]+/) {
    # Get the section number and its name
    $sec_num = $1;
    chop($_);
    $sec_header = substr($_, ((length($1)) + 1));
  }
  elsif (/Copyright.*IEEE. All rights reserved./) {
    $page_num = $page_num + 1;
    $curr_page = $page_num;
    if($curr_page > $page_offset){
      $curr_page = $curr_page - $page_offset;
    }
  }

  if (/$begintag(.*)/) {
    while (/$begintag(.*?)$endtag(.*)/) {
      $test_desc = $1;
      print "--------------------------------------------------------------------------------
TEST_NUM 
TEST_DESCRIPTION 
$test_desc
TEST_REFERENCE
IEEE P802.1ag/D7.1 Section $sec_num Page $curr_page '$sec_header'
TEST_METHOD
TEST_CLASSIFICATION
TCF_MUST\n";
      $test_desc ="";
      $_ = $2;
    }

    if (/$begintag(.*)/) {
      $isInsideTag = 1;
      $test_desc = $1;
    }
  }
}

close INFILE;
