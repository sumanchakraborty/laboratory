
#! /usr/bin/perl

open IN_FILE, "sample.txt" or die $!; 
open OUT_FILE, ">sample.bin" or die $!; 

binmode OUT_FILE;

# get each line of the file in the array
@array = <IN_FILE>;
$size = @array;

for($index = 0; $index < $size; $index++) {
  chop(@array[$index]);
  $line = @array[$index];
  print "--->$line-->$size\n";
  print OUT_FILE pack("Z8",$line); 

# print "$n bytes read\n"; 
# $buf .= $data; 
} 


close IN_FILE;
close OUT_FILE;


$line = "";

open IN_FILE, "sample.bin" or die $!; 
binmode IN_FILE;

$size = read(IN_FILE, $line, 8);
$unpacked = unpack("Z8", $line);

print "$line---$unpacked";

close IN_FILE;
