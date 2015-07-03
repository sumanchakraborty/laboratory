#! /usr/bin/perl

if (@ARGV != 3) {
  print"Usage: CompareTestNumber.pl <INPUT_FILE_1> <INPUT_FILE_2> <OUTPUT_FILE>\n";
  exit 0;
}

$in1 = @ARGV[0];
$in2 = @ARGV[1];
$out = @ARGV[2];

# Open all files
  open(INFILE1, "$in1") || die "Can't open input.txt:$1";
  open(INFILE2, "$in2") || die "Can't open input.txt:$1";
  open(OUTFILE, ">$out") || die "Can't open input.txt:$1";

# get each line of the file in the array
  @array1 = <INFILE1>;
  @array2 = <INFILE2>;

if(@array1 == @array2){

    $size1 = @array1;
    $size2 = @array2;

  for($index = 0; $index <= $size1; $index++) {
    chop(@array1[$index]);
    chop(@array2[$index]);
    print OUTFILE "@array1[$index] | @array2[$index]\n";
  }
  
}
else{
  print"Usage: line number of both input file MUST be same\n";
}
  
# Close all files
  close INFILE1;
  close INFILE2;
  close OUTFILE;

