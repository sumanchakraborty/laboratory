#! /usr/bin/perl

  print"Usage: ReplacePattern.pl <INITIAL-PATTERN> <FINAL-PATTERN> <NO-OF-FILES> <FILE-1> <FILE-2> ...\n";

  $init   = @ARGV[0];
  $final  = @ARGV[1];
  $fileNo = @ARGV[2];

for($loopIndex = 0; $loopIndex < $fileNo; $loopIndex++){

  $in     = @ARGV[3+$loopIndex];

  open(infile, "$in") || die "Can't open file $in :$1";
  open(outfile, ">xxx") || die "Can't open file xxx:$1";

  # get each line of the file in the array
    $count = 0;
    @array = <infile>;
    $size = @array;

    # for each line in the input file
    for($index = 0; $index <= $size; $index++) {
      chop(@array[$index]);
      $line = @array[$index];

      # replace resired pattern
      if ($line =~ s/$init/$final/g){
        $count++;
      }
      print outfile "$line\n";
    }

    system("cp xxx $in");

  # print the total test number
    print "########################\n";
    print "In file \"$in\" the pattern \n";
    print "\"$init\" is replaced with \"$final\"\n";
    print "The total occurence is $count\n";
    print "########################\n";

  close infile;
  close outfile;
}  
