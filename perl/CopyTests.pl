#! /usr/bin/perl

our $num = 0;
our $count = 0;
our $status = 0;

if (@ARGV != 2) {
  print"Usage: CopyTest.pl <inlined_test_number> <INPUT_FILE> <OUTPUT_FILE>\n";
  exit 0;
}

$in  = @ARGV[0];
$out = @ARGV[1];

open(infile,"$in") || die "Can't open input.txt:$1";
open(outfile,">$out") || die "Can't open input.txt:$1";

@test_vector = ();
$tv_size = @test_vector;

# get each line of the file in the array
  @array = <infile>;
  $size = @array;

  for($tv_index = 0; $tv_index < $tv_size; $tv_index++) {
    
    for ($index = 0; $index <= $size; $index++) {

    $line = @array[$index];

    if($line =~ /BEGIN_TEST/){
      $begin_test = $index
    }

# save the line number
    if ($line =~ /TEST_NUM/){
      $num = @array[$index + 1];
      chop($num);

      if($num =~ /"$test_vector[$tv_index]"/) {
        $count = $begin_test;
        while (!($line =~ /END_TEST/)){
          print outfile @array[$count];
          $count++;
          $line = @array[$count];
        }
# for END_TEST
        print outfile @array[$count];
        break;
      }
      }
    }
  }


# print the total test number
  print "The total test count is @test_vector\n";

close infile;
close outfile;
