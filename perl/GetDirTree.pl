#!/usr/bin/perl


#! perl -slw
use strict;
use Data::Dumper;

sub hashdir{
    my $dir = shift;
    opendir my $dh, $dir or die $!;
    my $tree = {}->{$dir} = {};
    while( my $file = readdir($dh) ) {
        next if $file =~ m[^\.{1,2}$];
        my $path = $dir .'/' . $file;
        $tree->{$file} = hashdir($path), next if -d $path;
        push @{$tree->{'.'}}, $file;
    }
    return $tree;
}

my $tree = hashdir( shift );

print Dumper $tree;


