#!/usr/local/bin/perl

$total=0;

$test_num="";
$test_desc="";
$test_ref="";
$sections="";
$exact_ref="";
$test_method="";
$test_class="";
$new_test_class="";

$tnum=1;
$tdesc=2;
$tref=3;
$tmethod=4;
$tclass=5;

$command=0;

while (<>) {
  if (/TEST_NUM/) {
    $total++;
    $command=$tnum;
  }
  elsif (/TEST_DESCRIPTION/) {
    $command=$tdesc;
  }
  elsif (/TEST_REFERENCE/) {
    $command=$tref;
  }
  elsif (/TEST_METHOD/) {
    $command=$tmethod;
  }
  elsif (/TEST_CLASSIFICATION/) {
    $command=$tclass;
  }
  elsif (/--------------------------------------------------/) {
    if ($test_num != "") {
      # Dump test
      $new_test_class = "TCF_MUST";
      if (($test_desc =~ /MAY/i) ||
          ($test_desc =~ /CAN/i) ||
          ($test_desc =~ /COULD/i) ||
          ($test_desc =~ /MIGHT/i)) {
        $new_test_class = "TCF_MAY";
      }
      if (($test_desc =~ /SHOULD/i) ||
          ($test_desc =~ /SHALL/i) ||
          ($test_desc =~ /RECOMMEND/i)) {
        $new_test_class = "TCF_SHOULD";
      }
      if (($test_desc =~ /MUST/i) ||
          ($test_desc =~ /WILL/i)) {
        $new_test_class = "TCF_MUST";
      }

      # Push all these elements into an array for post processing

      if ($test_ref =~ /Setup Verification/) {
        $exact_ref = "0";
        $exact_page = "0";
        $exact_hdr = "Setup Verification Test";
        $primary_key = "$exact_ref.$exact_page";
      }
      else {
        $stripped_test_ref = $test_ref;
        $stripped_test_ref =~ s/NEGATIVE\n//;
        $stripped_test_ref =~ /^RFC 3775 Section (.*) Page (.*) '(.*)'/;
        $exact_ref = "$1";
        if ($exact_ref == "") {
          print "Null reference for test # $test_num";
          exit -1;
        }
        $exact_page = "$2";
        $exact_hdr = $3;
        $exact_page =~ s/^(\d\d)$/0$1/;
        $exact_page =~ s/^(\d)$/00$1/;
        $exact_ref =~ s/\.$//; # Remove terminal '.' character
        $exact_ref =~ s/^(\d)\./0$1\./; # Change leading single digit with 0<digit>
        $exact_ref =~ s/\.(\d)\./\.0$1\./; # Change middle single digit with 0<digit>
        $exact_ref =~ s/\.(\d)$/\.0$1/; # Change terminal single digit with 0<digit>
        $primary_key = "$exact_ref.$exact_page";
      }
      $sections =~ s/^,//;
      push @arr,
           [ $primary_key, $exact_hdr, $test_num, $test_desc, $test_ref, $test_method, $test_class, $exact_ref, $sections ];
    }
    $test_num="";
    $test_desc="";
    $test_ref="";
    $sections = "";
    $test_method="";
    $test_class="";
    $new_test_class="";
  }
  else {
    if ($command == $tnum) {
      $test_num = $_;
    }
    elsif ($command == $tdesc) {
      $test_desc .= $_;
    }
    elsif ($command == $tref) {
      $test_ref .= $_;
      $tmp_section = $test_ref;
      $tmp_section =~ /RFC 3775 Section (.*) Page /;
      if (($1 != "") && ($sections !~ /$1/)) {
        $sections .= ",$1";
      }
    }
    elsif ($command == $tmethod) {
      $test_method .= $_;
    }
    elsif ($command == $tclass) {
      $test_class = $_;
    }
  }
}

#print "Total tests parsed # $total\n"
#@sorted = sort { $a->[0] <=> $b->[0] } @arr;
@nsorted = sort { ($a->[0] cmp $b->[0]) } @arr;

$major=1;
$minor=1;
$minor_high = 1;
$prev_sec="0";
$curr_sec="0";
$actual_test_num = "";
$prev_sections = "";
$prev_header = "";
$num_negative = 0;
$tot_num_negative = 0;

# We need to create a csv file to keep track of test renumering
# -------------------------------------------------------------
open(MATRIX, ">test_change_matrix.csv") or die "Unable to open file 'test_change_matrix.csv' for writing: $!";
open(COVERAGE, ">test_coverage.txt") or die "Unable to open file 'test_coverage.txt' for writing: $!";

print "--------------------------------------------------------------------------------\n";
print "  /*\n";
print "  BEGIN_SECTION\n";
print "  SECTION_NUM\n";
print "  1\n";
print "  SECTION_HDR\n";
print "  Setup Verification Tests\n";
print "  END_SECTION\n";
print "  */\n";

for $i (0 .. $#nsorted) {
  if ($i > 0) {
    $prev_sections = $nsorted[$i-1][8];
    $prev_header = $nsorted[$i-1][1];
    if ($minor == 0) {
      print "Error: Underflow on variable minor\n";
      exit -1;
    }
    $minor_high = $minor - 1;
    if ($nsorted[$i-1][4] =~ /NEGATIVE/) {
      $num_negative++;
    }
  }
  $prev_sec = $curr_sec;
  $curr_sec = $nsorted[$i][7];
  $curr_sec =~ s/\.$//; # Remove terminal '.' character
  if (($prev_sec cmp $curr_sec) != 0) {
    # First create coverage table
    $prev_major = $major;
    printf COVERAGE "| %7s | %50s | %2d.1-%2d.%2d    |\n",
                    $prev_sections,$prev_header,$prev_major,$prev_major,$minor_high;

    if ($num_negative > 0) {
      print COVERAGE "|         |                                                    | (Negative: $num_negative) |\n";
      $tot_num_negative += $num_negative;
    }
    print COVERAGE "+---------+----------------------------------------------------+---------------+\n";
    $num_negative = 0;
    # Now proceed with rest of creation
    $minor = 1;
    $major = $major + 1;
    print "--------------------------------------------------------------------------------\n";
    print "  /*\n";
    print "  BEGIN_SECTION\n";
    print "  SECTION_NUM\n";
    print "  $major\n";
    print "  SECTION_HDR\n";
    print "  $nsorted[$i][1]\n";
    print "  END_SECTION\n";
    print "  */\n";
  }
  elsif ($minor > 32) {
    # First create coverage table
    $prev_major = $major;
    print COVERAGE "$prev_sections | $prev_header | $prev_major.1-$prev_major.$minor_high (Negative: $num_negative)\n";
    $num_negative = 0;
    # Now proceed with rest of creation
    $major = $major + 1;
    $minor = 1;
    print "--------------------------------------------------------------------------------\n";
    print "  /*\n";
    print "  BEGIN_SECTION\n";
    print "  SECTION_NUM\n";
    print "  $major\n";
    print "  SECTION_HDR\n";
    print "  $nsorted[$i][1] (Contd.)\n";
    print "  END_SECTION\n";
    print "  */\n";
  }
  chomp $nsorted[$i][2];
  print MATRIX "$nsorted[$i][2],$major.$minor\n";
#  printf "prev : $prev_sec, and current: $curr_sec\n";
  print "--------------------------------------------------------------------------------\n";
#  print "TEST_NUM\n$nsorted[$i][3]";
  print "TEST_NUM\n$major.$minor\n";
  print "TEST_DESCRIPTION\n$nsorted[$i][3]";
  print "TEST_REFERENCE\n$nsorted[$i][4]";
  print "TEST_METHOD\n$nsorted[$i][5]";
  print "TEST_CLASSIFICATION\n$nsorted[$i][6]";
  $minor = $minor + 1;
}

$total_num = $#nsorted + 1;
print COVERAGE "|         |                                              Total | $total_num           |\n";
print COVERAGE "|         |                                                    | (Negative: $tot_num_negative)|\n";

close MATRIX;
close COVERAGE;
