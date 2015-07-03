#! /usr/bin/perl

if (@ARGV != 2) {
  print"Usage: CompareTestNumber.pl <INPUT_FILE_1> <OUTPUT_FILE>\n";
  exit 0;
}

$in1 = @ARGV[0];
$out = @ARGV[1];


my $state = 0;
my $start = 0;
my %hash = ();
my @testnums;
my @sortedtn;
my $buf = "";




open(OUTFILE, ">$out") || die "Can't open input.txt:$1";

# determine the input file size
open(INFILE1, "$in1") || die "Can't open input.txt:$1";

# compare each line of the larger
# file with each line of the 
# smaller file
while(<INFILE1>)
{
  if ($start == 1) {
    $buf = $buf . $_;
  }

  if (/TEST_REFERENCE/) {
    $state = 1;
  } elsif (/TEST_NUM/) {
    $start = 1;
    $buf = $_;
  } elsif (/TCF_MUST/) {
    push @{ $hash { $testno } } ,$buf;
    $start = 0;
    $buf = "";
  }
  
     
  if ($state == 1) {
    if (/(((\d)+\.)+)\s+(.*)/) {
#@testnum=(@testnum,$1);
      $testno = $1;
      $state = 0;
    }
  }
  
}

@in = keys %hash;
#$foo = shift @in;
#print join("\n",@in);
$tstr = "--------------------------------------------------------------------------------\n";
$majorcnt = 1;
$minorcnt = 1;
foreach $key (sort mysort @in) {
  $minorcnt = 1;
  @foo = @{ $hash{$key} };
  foreach $keymem (sort mysort1 @foo) {
#if ($keymem =~ /TEST_NUM((\s*)\n(\d)+(\.)(\d)*)/sg) {
#      unshift @foo,$1;
#    }
    $keymem =~ s/TEST_NUM(\s*)\n(\d+)(\.)(\d*)/TEST_NUM\n$majorcnt\.$minorcnt/sg;
    print $2,$3,$4,"----", $majorcnt,".",$minorcnt,"\n";
    print OUTFILE $keymem;
    print OUTFILE $tstr;
    $minorcnt++;
  }
  $majorcnt++;
}
#foreach $t (sort mysort @foo) {
#  print $t;
#}
#for my $sender ( sort keys %hash ) {
#    print "$sender: $hash{$sender}\n";
#    }
#@sortedtn = sort(@testnum);

#$string = join("\n",@sortedtn);
#print $string;

   
# Close all files
close INFILE1;
close OUTFILE;
exit;

sub mysort {
#print $a;
#print $b;
         @temp1 = split(/\./,$a);
         @temp2 = split(/\./,$b);
         if (@temp1[0] < @temp2[0]) {
           return -1;
         }
         elsif (@temp1[0] > @temp2[0]) {
          return 1;
         }
         elsif (@temp1[1] < @temp2[1]) {
          return -1;
         }
         elsif (@temp1[1] > @temp2[1]) {
          return 1;
         }
         elsif (@temp1[2] < @temp2[2]) {
          return -1;
         }
         elsif (@temp1[2] > @temp2[2]) {
          return 1;
         }
         else {
           return 0;
         };
         return 0;
       }

sub mysort1 {
          if ($a =~ /Page(\s*)(\d+)/s) {
            $tmp1 = $2;
          }
          if ($b =~ /Page(\s*)(\d+)/s) {
            $tmp2 = $2;
          }
          return $tmp1 <=> $tmp2;
         }

