<%perl>
 use File::Copy;
 use File::Touch;
 my $cwd = $m->base_comp->source_dir;
 if($ARGS{o} && $ARGS{f}){
   if($ARGS{o} eq 'm'){
     touch("$cwd/../mp3/incomplete/$ARGS{f}");
     move("$cwd/../mp3/incomplete/$ARGS{f}" => "$cwd/../mp3");
   }
   elsif($ARGS{o} eq 'c'){
     touch("$cwd/../mp3/incomplete/$ARGS{f}");
     copy("$cwd/../mp3/incomplete/$ARGS{f}" => "$cwd/../mp3");
   }
   elsif($ARGS{o} eq 'd'){
     unlink "$cwd/../mp3/incomplete/$ARGS{f}";
   }
   print "<script> window.location = 'admin.html?c=li' </script>";
 }
</%perl>
% use IO::All;
% my @incoming = sort {(stat("$a"))[9] <=> (stat("$b"))[9]} grep{/\.mp3/o} io("$cwd/../mp3/incomplete")->all_files();


% if (@incoming){
<h2> INCOMING </h2>

<table>
<tr> <td> NAME <td> SIZE (bytes)
<ul>
% use URI::Escape;
% foreach my $f (@incoming){
%  my $size = (stat("$f"))[7];
%  $f =~ s,^.+/,,;
<tr> 
 <td> <li> <% $f %>
 <td> <% $size %>
% if($ARGS{is_admin}){
%  my @cmd = ([m => 'Move out'], [c => 'Copy out'], [d => 'Delete']);
%  foreach (@cmd){
 <td> <a href="admin.html?c=li&o=<% $_->[0] %>&f=<% uri_escape $f %>">&lt;<% $_->[1] %>&gt;</a>
%  }
% }
%}
</ul>
</table>

% }
