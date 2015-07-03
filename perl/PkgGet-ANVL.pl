#! /usr/bin/perl

if (@ARGV != 3) {
  print"Usage: PkgGet-ANVL.pl <path> <version> <project>\n";
  exit 0;
}

$path = @ARGV[0];
$version  = @ARGV[1];
$project = @ARGV[2];

print("cd $path");
print("\np4-getro.pl -b anvl-$version-branch");
print("\nmake Proj-$project");
print("\nmake all");
print("\n");

#system("cd $path");
#chdir("$path") || die "cannot cd to $path ($!)";
system("p4-getro.pl -b anvl-$version-branch");
system("make Proj-$project");
system("make all");

