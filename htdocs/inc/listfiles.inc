<%perl>
 my $cwd = $m->base_comp->source_dir;
 if ($ARGS{o} eq 'd' && $ARGS{f}){
  unlink "$cwd/../mp3/$ARGS{f}";
#  print "$cwd/../mp3/$ARGS{f}";
  print "<script> window.location = 'admin.html?c=lf' </script>";
 }
</%perl>

% my @files = sort {(stat("$a"))[9] <=> (stat("$b"))[9]} grep{/\.mp3/o} io("$cwd/../mp3")->all_files();

% if(@files){
<h2> RIPPED FILES </h2>
% }

<table border=1>


% if( @files ){
<tr>
%  if($ARGS{is_admin}){
 <td>
%  }
 <td> NAME
 <td> LENGTH
 <td> FREQUENCY
 <td> STEREO
 <td> SIZE (Mb)
% }

<%perl>
use IO::All;
use MP3::Info;
use URI::Escape;


foreach my $f (@files){
 my $size = (stat("$f"))[7];
 my $info = get_mp3info("$f");

 $f =~ s,^.+/,,;
</%perl>

<tr>
% if($ARGS{is_admin}){
 <td align=left> <a href="admin.html?c=lf&o=d&f=<% uri_escape $f %>"> Delete </a>
% }
 <td align=left> <a href="mp3/<% uri_escape $f %>"> <% $f %> </a>
 <td align=right> <% $info->{TIME} %>
 <td align=right> <% $info->{FREQUENCY} %>
 <td align=right> <% $info->{STEREO} ? 'Y' : 'N' %>
 <td align=right> <% sprintf("%.5s", ($info->{SIZE}/1048576)) %>

%}

</table>

