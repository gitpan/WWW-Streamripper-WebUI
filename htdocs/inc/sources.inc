% my $cwd = $m->base_comp->source_dir;

<h2> SOURCES </h2>

<table>

<%perl>
use YAML;
use Digest::MD2 qw(md2_hex);

my $source = YAML::LoadFile("$cwd/../config/stream_source") or die "Source?";
if($ARGS{o} eq 'd' && defined $ARGS{id}){
  delete $source->{$ARGS{id}};
  YAML::DumpFile("$cwd/../config/stream_source", $source);
  print '<script> window.location = "admin.html?c=ls"; </script>'
}

if( $ARGS{name} && $ARGS{stream} && $ARGS{homepage} ){
 $source->{ md2_hex(join q//, $ARGS{name}, $ARGS{stream}, $ARGS{homepage}) } = 
   { map{ $_ => $ARGS{$_} } qw(name homepage stream schedule) };
 YAML::DumpFile("$cwd/../config/stream_source", $source);
}

my $sch = YAML::LoadFile("$cwd/../config/stream_schedule") or die "Source?";
foreach my $id (sort keys %$source){
   my $s = $source->{$id};
</%perl>

<tr>
 <td align=left> <a href='<% $s->{home} %>'> <% $s->{name} %> </a>
 <td> <a href='<% $s->{url} %>'> (STREAM) </a>
 <td> <% $s->{sch} ? "<a href='$s->{sch}'> (PROGRAMS) </a>" : '' %>
 <td>
% if(ref $sch->{$id}){
%  if($ARGS{is_admin}){
    <a href='admin.html?c=rsch&id=<% $id %>'> (SCHEDULE) </a>
%  }
% }

% if($ARGS{is_admin}){
 <td> <a href='admin.html?c=ls&o=d&id=<% $id %>'> (DELETE) </a>
 <td>
 <td>
  <table border=1>
   <form method="get" action="admin.html" enctype="application/x-www-form-urlencoded">
     <input type='hidden' name='c' value='rb'>
     <input type='hidden' name='o' value='rin'>
     <input type='hidden' name='id' value='<% $id %>'>
    length: <input type='text' name='sec' value='60' size=5> secs
     <input type='submit' value='Rip it now!'>
   </form>
  </table>
% }

</tr>

% }
</table>


% if($ARGS{is_admin}){
<h2> ADD NEW SOURCE </h2>
<form name='addsource' action="admin.html?c=ls" method="post" enctype="application/x-www-form-urlencoded">
<table>
<tr> <td> NAME         <td> <input type='text' name='name'>
<tr> <td> HOMEPAGE URL <td> <input type='text' name='homepage'>
<tr> <td> STREAM URL   <td> <input type='text' name='stream'>
<tr> <td> SCHEDULE URL <td> <input type='text' name='schedule'>
<tr> <td> <input type='submit' value="Add">
</table>
</form>

% }
