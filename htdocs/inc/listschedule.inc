<%perl>
my $cwd = $m->base_comp->source_dir;

my $schedule = YAML::LoadFile("$cwd/../config/stream_schedule");
my $source = YAML::LoadFile("$cwd/../config/stream_source");
use YAML;

</%perl>

<h2> SCHEDULES </h2>

<table>
% my @day = qw(Sun Mon Tue Wed Thr Fri Sat);
% foreach my $id (keys %$schedule){
%  foreach my $t (@{$schedule->{$id}}){
    <tr>
       <td> <% $source->{$id}->{name} %>
       <td> 
         <table>
%            foreach (@{$schedule->{$id}}){
              <tr>
	       <td> <% $_->[0] %>
	       <td> (<% $_->[1] %> secs)
	       <td> <% length($_->[2]) ? 
	                 ('@ ', join q/,/, map{$day[$_]} split /,/o, $_->[2]) :
			  ' every day' %>
%            }
	 </table>
    <tr> <td> <hr/>
%  }
%}
</%perl>

</table>

% if($ARGS{is_admin}){
% }
