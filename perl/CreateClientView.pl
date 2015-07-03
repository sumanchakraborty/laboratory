#!/usr/bin/perl
#
# p4-getro.pl [-b <exisiting-branch>]
# 
# Copyright (c) Ixia 2003
# All rights reserved
#
# DESCRIPTION: 
# This script is used to solve the "Chicken and Egg" Problem of wanting to 
# get Top-Level ANVL Makefiles from Perforce without a view.  The problem
# is retreiving the correct files without having to know details about the 
# Perforce Depot.
#
# ARGS:
# no args => trunk **OR**
# -b <exisiting-branch> => existing branch in P4
#
# PREREQUISITES:
# The user is encouraged to refer to www.perforce.com before using this script
# for details on any P4 commands.

################################################################################

# Global Variables

my $DEBUG_OFF = 0;

my $PWD = `pwd -L | cat`;
chop $PWD;

my $HOSTNAME = `hostname`;
chop $HOSTNAME;

################################################################################

# Perforce Environment Variables

# In order to have a truly unique client name we need to construct a client
# name as our current working directory structure with the reserved character
# underscore as seperator.  We also append _<username>_<hostname> so that 
# developers using multiple machines and multiple local builds do not overwrite
# their own environments accidentally or another developer's environment.
my $P4CLIENT = $PWD;
$P4CLIENT =~ s/^\///;
$P4CLIENT =~ s/\//_/g;
$P4CLIENT .= "_$ENV{P4USER}_$HOSTNAME";

# assume a default of ANVL trunk if no branch or other product specified
# (i.e. no arguments passed to script causes us to fall through main while
# loop)
my $P4DEPOT = "packages/ixnetwork_anvl_engine";

# assume a branch value of trunk implies ANVL trunk build
my $P4BRANCH = "trunk";

my $P4EDITOR = "/usr/local/scripts/p4-editor.pl";

my $P4DIFF = "/usr/local/scripts/tkdiff";

my $P4MERGE = "/usr/local/scripts/p4-merge.pl";

################################################################################

# Script Main Body

while ($ARGV[0]) {
    $OPTS = $ARGV[0];
    shift(@ARGV);

    if ($OPTS eq "-b") {
	$P4BRANCH = shift(@ARGV);
	
	if (!$P4BRANCH) {
	    $P4BRANCH = "trunk";
	    $P4DEPOT = "packages/ixnetwork_anvl_engine";
	}
	elsif ($P4BRANCH eq "trunk") {
	    $P4DEPOT = "packages/ixnetwork_anvl_engine";
	}
	else {
	    $EXISTS = `p4 branches | grep $P4BRANCH`;

	    if (!$EXISTS) {
		print "! Branch $P4BRANCH does NOT exist in Perforce\n";
		exit -1;
	    }
	       
	    $P4DEPOT = "packages/ixnetwork_anvl_engine/$P4BRANCH";
	}
    }
    else {
	P4Usage();
	exit -1;
    }
}

P4CONFIGCreate();
P4GNUMakefilesGet();

################################################################################
#
# P4ConfigCreate()
#
# DESCRIPTION:
# Creates the .perforce file used by the P4CONFIG Perforce environment variable.
# The .perforce file controls all p4 commands issued within a given directory.
# This allows one to switch back and forth between multiple product directories.
#
# ASSUMPTIONS:
# In order to create .perforce it is assumed that the user has supplied the
# values equivalent to examples below in ~/.bashrc or exported them before hand
# as appropriate:
#
#       export P4CONFIG=.perforce 
#       export P4USER=<your_username>
#       export P4PORT=perforce:1666
#
# RETURNS
# none
#
###
sub P4CONFIGCreate() {

    print "%% Creating P4CONFIG file (.perforce)\n";
    open (P4CONFIG, "> .perforce");
    
    print P4CONFIG "P4CLIENT=$P4CLIENT\n";
    print P4CONFIG "P4EDITOR=$P4EDITOR\n";
    print P4CONFIG "P4DIFF=$P4DIFF\n"; 
    print P4CONFIG "P4MERGE=$P4MERGE\n";
    print P4CONFIG "P4BRANCH=$P4BRANCH\n";
    print P4CONFIG "P4DEPOT=$P4DEPOT\n";
    
    close (P4CONFIG);
    
    $RESULT = `cat .perforce`;
    
    print "$RESULT\n\n" unless $DEBUG_OFF;
}

################################################################################
#
# P4GNUMakefilesGet()
#
# DESCRIPTION:
# Retrieves Top-Level ANVL GNUMakefiles from Perforce
#
# RETURNS
# none
#
###
sub P4GNUMakefilesGet() {

    # obtain a client spec based upon our .perforce settings and remove
    # any existing views so we can use the header part for our own
    # client spec
    my $PERFORCE_HEADER = `p4 client -o`;
    $PERFORCE_HEADER =~ s/\/\/.*//g;
    $PERFORCE_HEADER =~ s/\"//g;
    $PERFORCE_HEADER =~ s/LineEnd.*/LineEnd:\tunix/g;
   

    # when creating a new directory from scratch, we need to construct a client
    # view as part of the client spec that includes all the Top-Level makefiles
    # needed to do a gmake Proj-Foo and a gmake all

    $PERFORCE_VIEW = 
	"  //$P4DEPOT/...  //$P4CLIENT/...\n";
    
    open (CLIENT_SPEC, "> clientspec.proj");
    
    print CLIENT_SPEC "$PERFORCE_HEADER\n";
    print CLIENT_SPEC "$PERFORCE_VIEW\n";
    
    print "%% Creating Temporary Top-Level Makefile View\n";
    
    print "\n\n$PERFORCE_HEADER\n" unless $DEBUG_OFF;
    print "$PERFORCE_VIEW\n" unless $DEBUG_OFF;
    
    $RESULT = `p4 client -i < clientspec.proj`;
    
    print "$RESULT\n\n" unless $DEBUG_OFF;
    
#    $RESULT = `p4 sync -f`;
    
#    print "%% Syncing Top-Level Makefiles\n";
    
#    print "\n\n$RESULT\n\n" unless $DEBUG_OFF;
    
    $RESULT = `rm clientspec.proj`;
    
    print "%% Deleting Temporary Top-Level Makefile View\n";
    
    close (CLIENT_SPEC);
}

################################################################################
#
# P4Usage()
#
# DESCRIPTION:
# Usage string is printed on detection of command line argument error.
#
# RETURNS
# none
#
###
sub P4Usage() {
    my $ANVL_BRANCHES = `p4 branches | grep -i anvl`;
    $ANVL_BRANCHES =~ s/Branch //g; 
    $ANVL_BRANCHES =~ s/ .*//g; 
    $ANVL_BRANCHES =~ s/(.*)/                \1/g; 

    print "\nUSAGE: p4-getro.pl [-b <exisiting-branch>] \n\n";
    print "         where <existing-branch> is one of:\n";
    print "                trunk\n";
    print "$ANVL_BRANCHES\n";
}

################################################################################

