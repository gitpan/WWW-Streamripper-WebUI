<%perl>
if($ARGS{is_admin}){
  use Proc::ProcessTable;
  use Proc::Killfam;

  if($ARGS{o} && $ARGS{pid}){
    killfam 'SIGTERM', $ARGS{pid};
    print "<script> window.location = 'admin.html?c=shb' </script>";
  }

  my $t = new Proc::ProcessTable;
  print "<table border=1>";
  print "<tr> <td> <td> PID <td> STAT <td> START TIME <td> COMMAND";
  foreach my $p ( @{$t->table} ){
    my $cmd = $p->cmndline;
    if( $cmd =~ /(get_streams\.pl|streamripper)/o){
      $cmd =~ s,^.+perl ,,o;
      $cmd =~ s,\b(rin|daemon)\b,<b>$1</b>,g;
</%perl>
     <tr>
      <td> <a href="admin.html?c=shb&o=k&pid=<% $p->pid %>"> KILL </a>
      <td> <% $p->pid %>
      <td> <% $p->state %> 
      <td> <% scalar(localtime($p->start)) %>
      <td> <% $cmd %> </td>
<%perl>
    }
  }
  print "</table>";
}

</%perl>
