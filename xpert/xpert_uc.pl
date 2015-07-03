#!/usr/bin/perl      

# util code file
# --------------

# use package module   
use XML::Simple;
use Data::Dumper;
use strict;
use warnings;
use syntax;

my $protocol="bfd";
my $define;
my $ifile;
my $ofile_h;
my $ofile_c;
my $xml;
my $data;
my $prefix;
my $member;

#get input file name
$ifile   = $protocol."util.xml";
$ofile_h = $protocol."util.h";
$ofile_c = $protocol."util.c";

open(ofile_h, ">$ofile_h") || die "Can't open $ofile_h";
open(ofile_c, ">$ofile_c") || die "Can't open $ofile_c";

# create object   
$xml = new XML::Simple;      

# read XML file   
$data   = $xml->XMLin($ifile);
$prefix = $data->{name};

# access XML data   

# create definations
  foreach $define (@{$data->{define}}) {
    print ofile_h $DEFINE.$SPACE.$prefix.$USCORE;
    print ofile_h $define->{type}.$USCORE;
    print ofile_h $define->{subtype}.$SPACE;
    print ofile_h $define->{value}.$NEWLINE;
  }

  print ofile_h $NEWLINE;

# create enumeration
  print ofile_h $ENUM.$SPACE;
  print ofile_h $prefix.$data->{enum}->{name}."_e";
  print ofile_h $SPACE.$OBRACE_2;
  print ofile_h $NEWLINE;
  foreach $member (@{$data->{enum}->{member}}) {
    print ofile_h $TAB;
    print ofile_h $prefix.$USCORE;
    print ofile_h $member->{type}.$USCORE;
    print ofile_h $member->{subtype}.$COMMA.$NEWLINE;
  }
  print ofile_h $CBRACE_2.$SPACE.$SEMICOLON.$NEWLINE;
  print ofile_h $TYPEDEF.$SPACE.$STRUCT.$SPACE;
  print ofile_h $prefix.$data->{enum}->{name}."_e".$SPACE;
  print ofile_h $prefix.$data->{enum}->{name}."_t";
  print ofile_h $SEMICOLON.$NEWLINE;

  print ofile_h $NEWLINE;

# create structure format
  print ofile_h $STRUCT.$SPACE.$prefix."Form_s".$SPACE.$OBRACE_2;
  print ofile_h $NEWLINE;
  foreach $member (@{$data->{struct}->{member}}) {
    print ofile_h $TAB;
    print ofile_h $member->{size}.$SPACE;
    print ofile_h $member->{type};
    print ofile_h $SEMICOLON.$NEWLINE;
  }
  print ofile_h $CBRACE_2.$SPACE.$SEMICOLON.$NEWLINE;
  print ofile_h $TYPEDEF.$SPACE.$STRUCT.$SPACE;
  print ofile_h $prefix."Form_s".$SPACE.$prefix."Form_t";
  print ofile_h $SEMICOLON.$NEWLINE;

# print ofile_h Dumper($data);
# print ofile_c Dumper($data);

close(ofile_h);
close(ofile_c);
