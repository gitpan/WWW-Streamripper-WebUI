use Test::More qw(no_plan);
use ExtUtils::testlib;
use WWW::Streamripper::WebUI;

mkdir 'tmp';
chdir 'tmp';

install;

ok(-d $_) foreach qw(bin config inc mp3);
ok(-r $_) foreach qw(admin.html index.html);

use Fcntl ':mode';
foreach (qw(config mp3 run)){
    ok(S_IRWXU && S_IRWXG && S_IRWXO);
}
