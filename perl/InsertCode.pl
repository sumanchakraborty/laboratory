#! /usr/bin/perl

sub hashdir{
    my $dir = shift;
    opendir my $dh, $dir or die $!;
    my $tree = {}->{$dir} = {};
    while( my $file = readdir($dh) ) {
        next if $file =~ m[^\.{1,2}$];
        my $path = $dir .'/' . $file;

        if ($path =~ /.*-common-functions.*\.exp$/){

          $writen=0;

          open(SCRIPT, "$path") || die "Can't open input.txt: $path";
          @SCRIPT_ORIGINAL = <SCRIPT>;
          close SCRIPT;

          system("p4 edit $path");

          open(SCRIPT, ">$path") || die "Can't open input.txt: $path";
          $SCRIPT_ORIGINAL_SIZE = @SCRIPT_ORIGINAL;
          for ($index = 0; $index < $SCRIPT_ORIGINAL_SIZE; $index++){
            if (($writen==0) && 
                ($SCRIPT_ORIGINAL[$index] =~ /^[ ]*[a-z]+/)){
              print SCRIPT @SCRIPT_INSERT;
              $writen=1;
            }
            print SCRIPT @SCRIPT_ORIGINAL[$index];
          }
          close SCRIPT;

#         system("p4 revert $path");
        }        
        $tree->{$file} = hashdir($path), next if -d $path;
    }
    system("p4 change -o > foo");
}

open(SCRIPT, "insert.txt") || die "Can't open input.txt: insert.txt";
@SCRIPT_INSERT = <SCRIPT>;
close SCRIPT;

my $tree = hashdir( shift );


