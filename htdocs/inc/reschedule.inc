% if ($ARGS{is_admin} && $ARGS{id}){
% my $cwd = $m->base_comp->source_dir;
% use YAML;

<%perl>
 my $valid_input = 1;
 $ARGS{starttime} =~ s/\s+//go;
 if($ARGS{starttime} && $ARGS{length}){
   if($ARGS{starttime} !~ /\d\d:\d\d/o ||
      $ARGS{length} !~ /^\d+$/o ||
      (length $ARGS{day} && $ARGS{day} !~ /[0-6]/o)
     ){
     print "<script> alert('<$ARGS{starttime}> <$ARGS{length}> <$ARGS{day}> : invalid'); </script>";
     print "Input invalid\n";
     $valid_input = 0;
   }
 }
</%perl>

<h2> SCHEDULE of <i> <% $ARGS{id} %> </i> </h2>
<table>

<%perl>
my $source = YAML::LoadFile("$cwd/../config/stream_source")
   or print "Cannot open source file";
my $sch = YAML::LoadFile("$cwd/../config/stream_schedule")
   or print "Cannot oepn schedule file?";

if($ARGS{o} eq 'd' && defined $ARGS{item}){
  undef $sch->{$ARGS{id}}->[$ARGS{item}];
  @{$sch->{$ARGS{id}}} = grep{ ref } @{$sch->{$ARGS{id}}};
  YAML::DumpFile("$cwd/../config/stream_schedule", $sch);
  print "<script> window.location = 'admin.html?c=rsch&id=$ARGS{id}'; </script>";
}
if($ARGS{starttime} && $ARGS{length} && $valid_input){
  push @{$sch->{$ARGS{id}}}, [ $ARGS{starttime}, $ARGS{length}, $ARGS{day} ];
  YAML::DumpFile("$cwd/../config/stream_schedule", $sch);
  print "<script> window.location = 'admin.html?c=rsch&id=$ARGS{id}'; </script>";
}

my $id = $ARGS{id};
my $s = $source->{$id};
</%perl>

% my $cnt = 0;
% my @day = qw(Sun Mon Tue Wed Thr Fri Sat);
% foreach (@{$sch->{$id}}){
   <tr>
    <td>
      <a href='admin.html?c=rsch&id=<% $ARGS{id} %>&o=d&item=<% $cnt %>'>
        delete &gt;&gt;
      </a>
    <td> <% $_->[0] %>
    <td> ( <% $_->[1] %> secs )
    <td> <% length($_->[2]) ? ('@ ', join q/,/, map{$day[$_]} split /,/o, $_->[2]) : ' every day' %>
%  $cnt++;
% }

</table>

<h2> CURRENT TIME </h2>
<p> <u> <% scalar localtime %> </u>

<h2> ADD NEW SCHEDULE </h2>

<form name='addschedule' action='admin.html?c=rsch&id=<% $ARGS{id} %>' method="post" enctype="application/x-www-form-urlencoded">
<table>
<tr> <td> START TIME <td> <input type='text' name='starttime' > <td> ( e.g. "00:00", "12:30" )
<tr> <td> LENGTH <td> <input type='text' name='length'> <td> (secs)
<tr> <td> DAY OF WEEK <td> <input type='text' name='day'> <td> ( e.g. 0 => Sunday, "1,2" => Monday and Tuesday ) ( blank is for all week )
<tr> <td> <input type='submit' value="Add">
</table>
</form>



% }
