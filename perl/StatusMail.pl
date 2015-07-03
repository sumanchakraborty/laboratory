#! /usr/bin/perl

#`gvim ./body`;
#`mail -s perl_mail schakraborty@ixiacom.com < body`;


my $sendmail = '/usr/sbin/sendmail';
open(MAIL, "|$sendmail");
print MAIL "From: schakraborty\@ixiacom.com\n";
print MAIL "To: schakraborty\@ixiacom.com\n";
print MAIL "Subject: perl_mail\n\n";
print MAIL "hello, how r you\n";
close(MAIL);
