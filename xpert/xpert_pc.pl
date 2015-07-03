#!/usr/bin/perl

# protocol code file
# ------------------

# use package module   
use warnings;
use XML::Parser;
use Time::localtime;
use Data::Dumper;
use xpert_syntax;

require xpert_utility;

my $prefix   = "BFD";
my $protocol = "bfd";
my $define;
my $ifile;
my $ofile_h;
my $ofile_c;
my $xml;
my $data;
my $member;

#get input file name
$ifile   = $protocol.".xml";
$ofile_h = $protocol.".h";
$ofile_c = $protocol.".c";

open(my $OFILE_H, ">$ofile_h") || die "Can't open $ofile_h";
open(my $OFILE_C, ">$ofile_c") || die "Can't open $ofile_c";

# create parser object & parse
# $parser = new XML::Parser(Style => Debug);
  $parser = new XML::Parser();

  $parser->setHandlers (Start   => \&xpert_handle_start,
                        End     => \&xpert_handle_end,
                        Default => \&xpert_handle_default);

# read file   
  $parser->parsefile($ifile);

# print $OFILE_H Dumper($data);

# print ofile_h $DNL;

# create enumeration
# print ofile_h $ENUM.$SPACE;
# print ofile_h $prefix.$data->{enum}->{name}."_e";
# print ofile_h $SPACE.$OBRACE_2;
# print ofile_h $NL;
# foreach $member (@{$data->{enum}->{member}}) {
#   print ofile_h $TAB;
#   print ofile_h $prefix.$USCORE;
#   print ofile_h $member->{type}.$USCORE;
#   print ofile_h $member->{subtype}.$COMMA.$NL;
# }
# print ofile_h $CBRACE_2.$SPACE.$SEMICOLON.$NL;
# print ofile_h $TYPEDEF.$SPACE.$STRUCT.$SPACE;
# print ofile_h $prefix.$data->{enum}->{name}."_e".$SPACE;
# print ofile_h $prefix.$data->{enum}->{name}."_t";
# print ofile_h $SEMICOLON.$NL;

# print ofile_h $NL;

# create structure format
# print ofile_h $STRUCT.$SPACE.$prefix."Form_s".$SPACE.$OBRACE_2;
# print ofile_h $NL;
# foreach $member (@{$data->{struct}->{member}}) {
#   print ofile_h $TAB;
#   print ofile_h $member->{size}.$SPACE;
#   print ofile_h $member->{type};
#   print ofile_h $SEMICOLON.$NL;
# }
# print ofile_h $CBRACE_2.$SPACE.$SEMICOLON.$NL;
# print ofile_h $TYPEDEF.$SPACE.$STRUCT.$SPACE;
# print ofile_h $prefix."Form_s".$SPACE.$prefix."Form_t";
# print ofile_h $SEMICOLON.$NL;

close($OFILE_H);
close($OFILE_C);


# subroutines -------------

sub xpert_handle_start
{
  my ($parseinst, $element, %attrs) = @_;

  SWITCH: {
            if($element eq "protocol") {
              &xpert_pc_header($OFILE_H, $prefix);
              last SWITCH;
            }
            if($element eq "define") {
              &xpert_define($OFILE_H, %attrs);
              last SWITCH;
            }
            if($element eq "enum") {
              last SWITCH;
            }
            if($element eq "struct") {
              last SWITCH;
            }
          }
}

sub xpert_handle_end
{
  my ($parseinst, $element, %attrs) = @_;

  SWITCH: {
            if($element eq "protocol") {
              &xpert_pc_footer($OFILE_H, $prefix);
              last SWITCH;
            }
            if($element eq "define") {
              last SWITCH;
            }
            if($element eq "enum") {
              last SWITCH;
            }
            if($element eq "struct") {
              last SWITCH;
            }
          }
}

sub xpert_handle_default
{
}

sub xpert_include
{
}

sub xpert_define
{
# create definations

  my ($FILE, %attrs) = @_;

  print $FILE $DEFINE.$SPACE.$prefix;

  foreach $key (sort keys %attrs) {
    if ($key eq "value") {
      print $FILE $SPACE.$attrs{$key};
    }
    else {
      print $FILE $USCORE.$attrs{$key};
    }
  }

  print $FILE $NL;
}

sub xpert_enum
{
}

sub xpert_struct
{
  my $FILE_H   = $_[0];
  my $FILE_C   = $_[1];
}

sub xpert_pc_header
{
  my $FILE   = $_[0];
  my $prefix = $_[1];

  print $FILE $COMMENT_START;
  print $FILE $NL.$TAB;
  print $FILE $prefix." Protocol Code";
  print $FILE $NL;

  xpert_utility::copyright($FILE);

  print $FILE $COMMENT_STOP;
  print $FILE $DNL;

# #ifndef __PROTO_H__
  print $FILE $IFNDEF.$SPACE.$USCORE.$USCORE;
  print $FILE $prefix.$USCORE."H";
  print $FILE $USCORE.$USCORE;

  print $FILE $NL;

# #define __PROTO_H__
  print $FILE $DEFINE.$SPACE.$USCORE.$USCORE;
  print $FILE $prefix.$USCORE."H";
  print $FILE $USCORE.$USCORE;

  print $FILE $DNL;

}

sub xpert_pc_footer
{
  my $FILE   = $_[0];
  my $prefix = $_[1];

  print $FILE $DNL;

# #endif /* __PROTO_H__ */
  print $FILE $ENDIF.$SPACE;
  print $FILE $COMMENT_START;
  print $FILE $USCORE.$USCORE;
  print $FILE $prefix.$USCORE."H";
  print $FILE $USCORE.$USCORE;
  print $FILE $COMMENT_STOP;

  print $FILE $DNL;
}
