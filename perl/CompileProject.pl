#! /usr/bin/perl

if (@ARGV != 1) {
  print"Usage: CompileProject.pl <PROJECT>;"
  exit 0;
}

$project = @ARGV[0];


mkdir /home/schakraborty/Proj/project;
cd /home/schakraborty/Proj/project;
p4-getro.pl;
make project;
make all;

# prepare docs
#if(@ARGV[0] == "-d") {
#  make docs;
#}

# prepare xANVL
#if(@ARGV[0] == "-g") {
#  make docs;
#  cp /home/schakraborty/Proj/itm .;
#  make xanvl ITM_BIN= ./itm;
#  make anvl.xml;
#}






