#! /usr/bin/perl

print "Usage: Status.pl \n";
print "/home/schakraborty/status/DailyStatus.txt\n";

# status file to be updated
$status = "/home/schakraborty/status/DailyStatus.txt";

open(infile, ">>$status") || die "Can't open :$status";

while(1){
  system ("echo \"############################\" >> $status");
  system ("date >> $status");
  system ("echo \"############################\" >> $status");
  system ("gvim $status");
  sleep 3600;
}

close infile;
