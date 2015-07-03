#! /usr/bin/perl

if (@ARGV != 3) {
  print"Usage: CompareTestNumber.pl <baseline.log> <current.log> <result>\n";
  print"       baseline.log - the baseline log with which comparision should be made\n";
  print"       current.log  - the new generated log for which analysis to be made\n";
  print"       result       - the output file of the analysis made by this script\n";
  exit 0;
}

$in1 = @ARGV[0];
$in2 = @ARGV[1];
$out = @ARGV[2];

my $count1 = 0;
my $count2 = 0;
my $status = "XXXXXX";

# Open all files
  open(INFILE1, "$in1") || die "Can't open input.txt:$1";
  open(INFILE2, "$in2") || die "Can't open input.txt:$1";
  open(OUTFILE, ">$out") || die "Can't open input.txt:$1";

# Correct format
  system("dos2unix $in1");
  system("dos2unix $in2");

while(<INFILE1>) {
  if($_ =~ /<</){
    @array1[$count1] = $_;
    $count1++;
  }
}

while(<INFILE2>) {
  if($_ =~ /<</){
    @array2[$count2] = $_;
    $count2++;
  }
}

# get each line of the file in the array
# @array1 = <INFILE1>;
# @array2 = <INFILE2>;

#if($count1 == $count2){

  printf OUTFILE "+ %-18s + %-18s + %-18s + %-18s\n", "", "", "", "";
  printf OUTFILE "| %-18s | %-18s | %-18s | %-18s\n", 
                           "test number", "old status", 
                           "new status", "regression status";
  printf OUTFILE "+ %-18s + %-18s + %-18s + %-18s\n", "", "", "", "";

  for($index = 0; $index < $count1; $index++) {

    $status = "XXXXXX";

    chop(@array1[$index]);
    chop(@array2[$index]);

    @spltd_array1 = split(/: /, $array1[$index]);
    @spltd_array2 = split(/: /, $array2[$index]);
 
    @spltd_array1[0] =~ s/.*<< //e;
    @spltd_array2[0] =~ s/.*<< //e;
 
    if(!(@spltd_array1[0] eq @spltd_array2[0])){
      $index = $count1;
      print "test number mismatch\n";
      print "   old test number - @spltd_array1[0]\n";
      print "   new test number - @spltd_array2[0]\n", ;
    }
    else{
      if(@spltd_array1[1] eq @spltd_array2[1]){
        $status = "Passed";
      }
      else{
######################
# PASS->*
######################
        if(@spltd_array1[1] eq "Passed"){
          $status = "Failed *";
        }
######################
# *->PASS
######################
        if(@spltd_array2[1] eq "Passed"){
          $status = "Passed";
        }
######################
# FAIL->*       
######################
        if(@spltd_array1[1] eq "FAILED"){
          $status = "Passed";
        }
######################
# *->INCONCLUSIVE
######################
        if(@spltd_array2[1] eq "INCONCLUSIVE"){
          $status = "Failed *";
        }
######################
# INCONCLUSIVE->*
######################
        if(@spltd_array1[1] eq "INCONCLUSIVE"){
          $status = "Passed";
        }
      }

      printf OUTFILE "| %-18s | %-18s | %-18s | %-18s\n", 
                     @spltd_array1[0], @spltd_array1[1], @spltd_array2[1], $status;
    }
  }
  printf OUTFILE "+ %-18s + %-18s + %-18s + %-18s\n", "", "", "", "";
#}
#else{
#  print "Number of tests run is different!!\n";
#}
  
# Close all files
  close INFILE1;
  close INFILE2;
  close OUTFILE;

