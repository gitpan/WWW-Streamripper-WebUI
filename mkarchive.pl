use strict;
use IO::All;
use Archive::Tar;
sub mkarchive {
    chdir "$ENV{PWD}/htdocs";
    my $skip = qr'(\.mp3|CVS\b|current_schedule|daemon_pid|~$)';
    my @file = map{"./$_"} grep{!/$skip/} io('.')->All();
    print map{ "Archiving $_\n" } @file;
    mkdir '../tmp';
    Archive::Tar->create_archive ("../tmp/webui.tar.gz", 9, @file);

    chdir "..";
    mkdir 'lib/WWW/Streamripper/WebUI';
    my $content = io('tmp/webui.tar.gz')->slurp;
    $content =~ s/(.)/sprintf("%2x", ord $1)/xeg;
    $content =~ s/\n/0a/g;
    $content =~ s/ /0/g;
    
    my $t = io('lib/WWW/Streamripper/WebUI.pm')->slurp;
    $t =~ s/sub tarball \{ '.+?' \}/sub tarball { '$content' }/;
    io('lib/WWW/Streamripper/WebUI.pm')->print($t);
    unlink "tmp/webui.tar.gz";
}

&mkarchive;
