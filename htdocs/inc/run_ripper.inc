<%perl>
if($ARGS{is_admin}){
  my $cwd = $m->base_comp->source_dir;
  if($ARGS{o} eq 'rin' && $ARGS{id}){
    system("$cwd/../bin/get_streams.pl rin $cwd/../mp3 $ARGS{id} $ARGS{sec}");
  }
  else {
    system("$cwd/../bin/get_streams.pl daemon $cwd/../mp3");
  }
  print "<script> window.location = 'admin.html?c=shb' </script>";
}
</%perl>
