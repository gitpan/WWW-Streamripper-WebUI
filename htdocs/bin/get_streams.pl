#!/usr/local/bin/perl
eval 'exec /usr/bin/perl  -S $0 ${1+"$@"}' if 0;

use strict;

use File::Copy;
use Data::Dumper;
use Proc::Daemon;
use YAML;
use IO::All;

Proc::Daemon::Init;

my $streamripper_bin = '/usr/local/bin/streamripper';

my ($type, $basedir) = @ARGV[0,1];
chdir $basedir;

my $source = YAML::LoadFile("$basedir/../config/stream_source") or die "Source?";

if($type eq 'rin'){
  # Rip It Now
  my ($id, $secs) = @ARGV[2,3];
  exit unless $source->{$id};
  exit unless $secs;
  exec($streamripper_bin, $source->{$id}->{url}, '-l', $secs, '-s');
}

elsif($type eq 'daemon'){
  my $pid_file = "$basedir/../run/daemon_pid";
  my $sch_file = "$basedir/../run/current_schedule";
  $SIG{TERM} = sub { unlink $pid_file, $sch_file; exit };
  END{ unlink $pid_file, $sch_file; }
  
  exit if -r $pid_file;

  while(1){
    my $schedule = YAML::LoadFile("$basedir/../config/stream_schedule") or die "Schedule?";
    chmod 0666, "$basedir/../config/stream_schedule";
    YAML::DumpFile($pid_file, $$);
    YAML::DumpFile($sch_file, $schedule);
    
    my $time = scalar localtime;
    my $day = (localtime)[6];
    
    foreach my $id (keys %$schedule){
      foreach my $t (@{$schedule->{$id}}){
	next unless defined $t->[0];
	next unless defined $t->[1];
	next unless $time =~ / $t->[0]/;
	next if length $t->[2] && $t->[2] !~ /\b$day\b/;
	
	my $pid = fork();
	if(!$pid){
	  exec($streamripper_bin, $source->{$id}->{url}, '-l', $t->[1], '-s');
	  exit;
	}
	last;
      }
    }
    sleep(60);
  }

}

__END__
