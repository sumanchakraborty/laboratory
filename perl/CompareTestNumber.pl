#! /usr/bin/perl

if (@ARGV != 3) {
  print"Usage: CompareTestNumber.pl <INPUT_FILE_1> <INPUT_FILE_2> <OUTPUT_FILE>\n";
  exit 0;
}

$in1 = @ARGV[0];
$in2 = @ARGV[1];
$out = @ARGV[2];


my $line = 0;
my $state = 0;

my $size_file1;
my $size_file2;

$size_file1 = -s $in1;
$size_file2 = -s $in2;


open(OUTFILE, ">$out") || die "Can't open input.txt:$1";

# determine the input file size
if( $size_file1 > $size_file2){
  open(INFILE1, "$in1") || die "Can't open input.txt:$1";
  open(INFILE2, "$in2") || die "Can't open input.txt:$1";
  print "@ARGV[0] is larger \n";
}
else {
  open(INFILE1, "$in2") || die "Can't open input.txt:$1";
  open(INFILE2, "$in1") || die "Can't open input.txt:$1";
  print "@ARGV[1] is larger \n";
}

# compare each line of the larger
# file with each line of the 
# smaller file
while(<INFILE1>)
{
  $state = 0;
  $line = $_;

  while(<INFILE2>){
    if($_ == $line){
      $state = 1;
    }
  }

  if($state == 0){
    print OUTFILE "$line";
  }

  seek(INFILE2, 0, "SEEK_SET");
}


# Close all files
close INFILE1;
close INFILE2;
close OUTFILE;
