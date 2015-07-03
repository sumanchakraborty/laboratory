#! /usr/bin/perl

if (@ARGV != 2) {
  print"Usage: PkgGet.pl <version> <project>\n";
  print"       <version> 7.20, 7.40, main etc.\n";
  print"       <project> Proj-IPDev, Proj-RIPDev etc.\n";
  exit 0;
}

#$path = @ARGV[0];
$version  = @ARGV[0];
$project = @ARGV[1];


############################################################
# Set Environment variables
############################################################
$ENV{"P4USER"} = "schakraborty";
$ENV{"P4PORT"} = "perforce:1666";
$ENV{"P4CONFIG"} = ".perforce";

system("unset LIB");
system("unset INCLUDE");


############################################################
# variables
############################################################
my $P4DEPOT = "packages/ixnetwork_anvl_engine/$version";
my $PWD = `pwd -L | cat`;
chop $PWD;
my $HOSTNAME = `hostname`;
chop $HOSTNAME;
my $P4CLIENT = $PWD;
$P4CLIENT =~ s/^\///;
$P4CLIENT =~ s/\//_/g;
$P4CLIENT .= "_$ENV{P4USER}_$HOSTNAME";

############################################################
# clear all required paths
############################################################
system("rm -rf package-$version");
system("rm -rf conformance-$version");

############################################################
# create move to conformance target
############################################################
system("mkdir conformance-$version");
chdir "conformance-$version";

############################################################
# build project
############################################################
system("echo y | p4-getro.pl -b anvl-$version-branch");
system("make $project");
system("make all");

############################################################
# create move to package target
############################################################
chdir "..";
system("mkdir package-$version");
system("cp -r conformance-$version/Bin/ix86-Win32/* package-$version/");
system("rm -rf conformance-$version");
#system("echo y | p4-getro-pkg.pl -b $version");

CreateClientView();
#AddPackage();










############################################################
# add package
############################################################
sub AddPackage() {

    print "%% adding package $version ...\n";
    $result = chdir "package-$version";
    system("echo y | AddPackage.pl -b $version");
    chdir "..";

}

############################################################
# create client view for package
############################################################
sub CreateClientView() {

    print "%% creating client view ...\n";
    $result = chdir "package-$version";
    system("echo y | CreateClientView.pl -b $version");
    chdir "..";
}
