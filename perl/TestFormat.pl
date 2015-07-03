#! /usr/bin/perl


if (@ARGV != 2) {
  print"Usage: Format.pl <FILE_IN> <FILE_OUT>\n";
  exit 0;
}

$file_in  = @ARGV[0];
$file_out  = @ARGV[1];

my $line;
my $new_sec = 0;
my $major = 0;
my $minor = 0;

open(file_i, "<$file_in")  || die "Can't open input.txt:$1";
open(file_o, ">$file_out") || die "Can't open input.txt:$2";

# get each line of the file file_name the array

  foreach $line (<file_i>) {

# got the section
    if ($line =~ /SECTION_NUM/){
      $new_sec = 1;
      print file_o $line;
      next
    }

# save the major number
    if ($new_sec == 1){
      $major = $line;
      chomp($major);
      $minor = 0;
      $new_sec = 0;
      print file_o $line;
      next
    }

# print test header
    if ($line =~ /BEGIN_TEST/){
      $minor = $minor + 1;
      print file_o "  /*** PIM-SM-$major.$minor *********************************************************/\n";
      print file_o $line;
      next
    }

    if ($line =~ /END_TEST/){
      print file_o "  END_TEST; /* PIM-SM-$major.$minor */\n";
      next
    }

    print file_o $line;
  }

# close all the files
close file_i;
close file_o;
