#!/usr/local/bin/perl
#
# testref.pl - generate test summary with reference from test assertion list
#
#  Copyright (c) Ixia 2002 
#  All rights reserved.
 
# $Header: /LOCAL-BUILD/yxabdulr/ALL/DocTAL/RCS/testref.pl,v 3.4 2002/08/28 18:07:49 yxabdulr Exp $
#
# $Log: testref.pl,v $
# Revision 3.4  2002/08/28 18:07:49  yxabdulr
# added copyright printout for every file generated
#
# Revision 3.3  2002/02/14 15:46:02  yxabdulr
# Added -All rights reserved.- after Copyright.
#
# Revision 3.2  2002/02/13 15:20:31  yxabdulr
# Remove existing copyright and add ixia copyright
#
# Revision 3.1  2000/08/07 21:49:21  yxabdulr
# Modified the routine so that it can take multiple line of info
#
# Revision 3.0  2000/03/15 22:36:17  marcel
# Initial check in.
#
# 
#

$inDoc = 0;
$thisYear = `/bin/date +%Y`;
# print copyright info at the top of the file
printf "Copyright (c) Ixia %s", $thisYear;
printf "All rights reserved\n\n";

while(<>){
	if(/TEST_NUM/){
		$inDoc = 1;
		$_ = <>;
		chop;
		printf "%-4s - ",$_;
	}
	elsif(/TEST_DESCRIPTION/){
		# print the first line of description.
		$_ = <>;
		chop;
		printf "%.72s\n", $_;   
		
		while($inDoc) {
			# get the next line
			$_ = <>;
			
			if(/TEST_REFERENCE/) {
				$inDoc = 0;
			}
			else {
				chop;
				printf "       " ;
				printf "%.72s\n",$_;
			}
		}
		#process reference section
		$inDoc = 1;
		while($inDoc) {
			$_ = <>;
			if(/TEST_METHOD/ || /SETUP/) {
				$inDoc = 0;
			}
			else {
				chop;
				printf "       " ;
				printf "%.72s\n",$_;
			}
		}
		printf "\n";
	}
}


