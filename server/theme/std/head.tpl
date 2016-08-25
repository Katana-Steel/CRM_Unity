<?php
$ret = "
<script language=\"JavaScript\">
function bugs()
{
open(\"/bugs.php?page=${request_uri}\",\"_blank\",\"HEIGHT=350,WIDTH=300\");
}
</script>
<table align=\"left\" border=\"0\" style=\"font-family: Arial;\">
<tr>
<!-- Left buffer zone -->
<td width=\"45\">&nbsp;</td>

<!-- Where the page is -->
<td>

 <table align=\"center\" width=\"100%\">
  <tr>
   <td align=\"left\" width=\"10%\">".(($type == "A") ? "<!--" : "") ."
    <a href=\"${scriptname}\"><img border=\"0\" height=\"75\" src=\"images/logo.png\" /></a>
	". (($type == "A") ? "-->" : "") ."
   </td>
   <td width=\"80%\">
    <table width=\"100%\" align=\"center\">
  <tr> <!-- name and address could go here -->
   <td align=\"center\" style=\"font-size: 10pt; font-style: italic; font-weight: bold;\">
    &nbsp;
   </td>
  </tr>
  <tr>
   <td align=\"center\" style=\"font-size: 6pt; font-style: italic; font-weight: bold;\">
    &nbsp;
   </td>
  </tr>
  <tr>
   <td align=\"center\" style=\"font-size: 6pt; font-style: italic; font-weight: bold;\">
    &nbsp;
   </td>
  </tr>
	</table>
   </td>
   <td align=\"right\" width=\"10%\">". (($type == "A") ? "<!--" : "") ."
    <img border=\"0\" height=\"75\" src=\"images/logo.png\" />
	". (($type == "A") ? "-->" : "") ."
   </td>
  </tr>
  <tr>
   <td colspan=\"3\">
    <table align=\"right\">
	<tr>
   <td align=\"right\" style=\"font-size: 14pt; font-weight: bold;\">
    ${str}
   </td>
   <td align=\"right\" width=\"85\" style=\"border: solid black 1px; font-size: 10pt; font-style: italic;\">
    ${id}&nbsp;
   </td>
	</tr>
";
if($rek != "" ) {
 $ret .= "
	<tr>
   <td align=\"right\" style=\"font-size: 12pt; font-weight: bold;\">
    Rekvisition:
   </td>
   <td align=\"right\" width=\"85\" style=\"border: solid black 1px; font-size: 8pt; font-style: italic;\">
    ${rek}
   </td>
	</tr>";
}
$ret .= "
	</table>
   </td>
</tr>
 </table>
";
?>
