#!/usr/local/bin/perl
#
# memdebug.pl
#

# +++it would be cool to add time stamps and see how long memory is alloc'd for

($me = $0) =~ s!^.*/!!;
$usage =
    "usage: $me [-help] [memfile...]\n" .
    " -help             print this message\n" .
    " memfile           one or more memdebug output files\n";

################################################################################
# Process arguments
#

while($_ = $ARGV[0], /^-/){
  $_ = shift;
  if(/^-help$/){
    die $usage;
  }
  else{
    die "Unknown option: $_\n$usage";
  }
}

###############################################################################
#
# Process input
#

%mallocHistory = ();
%mallocCount = ();
%freeCount = ();
%refCount = ();
$maxMemUsed = 0;
$maxMalloc = 0;
$currMemUsed = 0;
$totalMalloc = 0;
$totalFree = 0;
$totalLeak = 0;

$line = 0;
while(<ARGV>){
  $inputLine++;
  next unless /^MEMDEBUG:/;

  if(/^MEMDEBUG: (\S+):(\d+) Malloc of (\d+) bytes returned (0x[0-9A-Fa-f]+)/){
	$file = $1;
	$line = $2;
	$size = $3;
	$ptr = $4;

	# Check if we already have this ptr (we shouldn't)
	$history = $mallocHistory{$ptr};
	if($history){
	  (@h) = split(/:/, $history);
	  print "* $ptr returned by malloc() when not free at $h[0]:$h[1]\n";
	}

	# Store it and update stats
	$mallocHistory{$ptr} = "$file:$line:$size";
	$currMemUsed += $size;
	$maxMemUsed = $currMemUsed if($currMemUsed > $maxMemUsed);
	$maxMalloc = $size if ($size > $maxMalloc);
	$mallocCount{"$file:$line"}++;
	$refCount{"$file:$line"}++;
  }
  elsif(/^MEMDEBUG: (\S+):(\d+) Free of (0x[0-9A-Fa-f]+)/){
	$file = $1;
	$line = $2;
	$ptr = $3;

	# Look up the pointer
	$history = $mallocHistory{$ptr};
	if(!$history){
	  print "* $ptr free'd at $file:$line but not malloc'd\n";
	}
	else{
	  # clear it out and update stats
	  delete $mallocHistory{$ptr};
	  (@h) = split(/:/, $history);
	  $currMemUsed -= $h[2];
	}
	$freeCount{"$file:$line"}++;
  }
  else{
	die "Input Line $inputLine is bad:\n$_";
  }
}

# Compute malloc/free counts

foreach $k (keys %mallocCount){
  $totalMalloc += $mallocCount{$k};
}

foreach $k (keys %freeCount){
  $totalFree += $freeCount{$k};
}

print "\n" . "-" x 79 . "\n";
print "Malloc high-water mark: $maxMemUsed\n";
print "Largest Malloc: $maxMalloc\n";
print "Total Malloc calls: $totalMalloc\n";
print "Total Free calls: $totalFree\n";
print "Memory Leaks:\n";
print "\t                        malloc               " .
	  "total    total mallocs\n";
print "\tfile:line                size    # leaks     " .
	  "leak     at this line\n";
print "\t---------------------------------------------" .
	  "----------------------\n";

# Compute total leaks
%leakCount = ();
# create array that counts each malloc occurrance left over
foreach $k (keys %mallocHistory){
  $leakCount{$mallocHistory{$k}}++;
}

# display the results in alphabetical order by filename
foreach $k (sort keys %leakCount){
  (@h) = split(/:/, $k);
  $total = $h[2] * $leakCount{$k};
  $ref = "$h[0]:$h[1]";
  printf("\t%-20s %5d bytes * %3d = %6d bytes [%d refs]\n",
		 $ref,$h[2],$leakCount{$k},$total,$refCount{$ref});
  $totalLeak += $total;
}

print "Total Memory Leaked: $totalLeak\n";
print "-" x 79 . "\n\n";
