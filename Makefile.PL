use inc::Module::Install;

use strict;

name('WWW-Streamripper-WebUI');
abstract('Web interface to streamripper');
author('xern <xern@cpan.org>');
license('perl');
version('0.02');

requires('perl'             => 5.006);
requires('Test::More');
my %req = qw(
	   IO::All               0.14
	   MP3::Info             1.02
	     YAML                  0.35
	   Proc::ProcessTable    0.39
	   Proc::Killfam         1.0
	   Digest::MD2           2
	   HTML::Mason           1.25
	   Proc::Daemon          0.02
	   Archive::Tar          0.23
	   URI::Escape           3.22
	   File::Touch           0.01
	  );
foreach (keys %req){
  requires($_ => $req{$_});
}


&WriteMakefile();
