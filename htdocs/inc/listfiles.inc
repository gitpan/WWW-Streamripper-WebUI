<%perl>
 my $cwd = $m->base_comp->source_dir;
 if ($ARGS{o} eq 'd' && $ARGS{f}){
  unlink "$cwd/../mp3/$ARGS{f}";
#  print "$cwd/../mp3/$ARGS{f}";
  print "<script> window.location = 'admin.html?c=lf' </script>";
 }
 my $tostat = $ARGS{f};
</%perl>

% my @files = sort {(stat("$b"))[9] <=> (stat("$a"))[9]} grep{/\.mp3/o} io("$cwd/../mp3")->all_files();

% if(@files){
<h2> RIPPED FILES </h2>
% }

<table border=1>


% if( @files ){
<tr>
%  if($ARGS{is_admin}){
 <td>
%  }
   <td>
   <td> NAME
% }

<%perl>
use IO::All;
use MP3::Info;
use URI::Escape;

my $info;
my $cnt = 0;
foreach my $f (@files){
 $info = undef;
 $f =~ s,^.+/,,;
 $info = get_mp3info("$cwd/../mp3/$f") if $tostat && "$f" eq "$tostat";
</%perl>
<tr>
% if($ARGS{is_admin}){
 <td align=left> <a href="admin.html?c=lf&o=d&f=<% uri_escape $f %>"> Delete </a>
% }
 <td width=0> <a name="<% $cnt %>"></a> 
 <td align=left> <a href="mp3/<% uri_escape $f %>"> <% $f %> </a>
% if( ref $info ){
 <td>
  <table border=1>
   <tr> <td> LENGTH <td align=right> <% $info->{TIME} %>
   <tr> <td> FREQUENCY <td align=right> <% $info->{FREQUENCY} %>
   <tr> <td> STEREO <td align=right> <% $info->{STEREO} ? 'Y' : 'N' %>
   <tr> <td> SIZE (Mb) <td align=right> <% sprintf("%.5s", ($info->{SIZE}/1048576)) %>

  </table>
% } else {
 <td> <a href="<% $ARGS{is_admin}? 'admin.html' : 'index.html' %>?c=lf&f=<% uri_escape $f %>#<% $cnt-1 %>"> info </a>
% }
% $cnt++;
%}

</table>

