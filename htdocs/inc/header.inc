<%args>
 $title
</%args>
<head>
<title> <% $title %> </title>
<link rel="stylesheet" href="css/streamripper.css" type="text/css" />
% if($ARGS{timeout}){
<META HTTP-EQUIV=Refresh CONTENT="<% $ARGS{timeout} %>">
%}
<META Http-Equiv="Cache-Control" Content="no-cache">
<META Http-Equiv="Pragma" Content="no-cache">
<META Http-Equiv="Expires" Content="0">
</head>

