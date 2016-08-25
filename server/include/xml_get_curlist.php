<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_get_curlist.php is part of Helhed Client.

    Helhed Client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/
?>
<?php
$sql = "select * from `kunde` where kundenr=$knr";
$res = mysql_query($sql,$link);
$knd = mysql_fetch_assoc($res);
$id = $knd['id'];
$msub = "Vare Liste på kunde nr: $knr";
$sql = str_replace("where (", "where (kunde_nr=$id) and (", str_replace("\\","",funicode($save)));
$msg = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"".
       " \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
<!-- $sql -->
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />
<title>$msub</title>
</head>
<body>";
global $rpath;
$file = $_SERVER['DOCUMENT_ROOT'] . $rpath . "/style/style.css";
$s = file_get_contents($file);
$msg .= "<style>\n$s\n</style>\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">".
        "</head>\n<body>\n".order_head("","","","");
$msg .= "
<table align=\"center\" width=\"100%\">
 <tr>
  <td width=\"50%\">
   <table class=\"bdrall\">
	<tr>
	 <td width=\"70\">Kundenr:</td>
	 <td width=\"200\">".$knd["kundenr"]."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $knd["firma"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $knd["navn"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $knd["adresse"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $knd["post"] ." ". $knd["by"] ."</td>
	</tr>";
if($knd["EAN_SE"] != "") {
	if(strtolower($knd["land"]) == "danmark") {
$msg .= "
	<tr>
	 <td>EAN</td>
	 <td>". $knd["EAN_SE"] ."</td>
	</tr>";
	} else {
$msg .= "
	<tr>
	 <td></td>
	 <td>". $knd["land"] ."</td>
	</tr>
	<tr>
	 <td></td>
	 <td>". $knd["EAN_SE"] ."</td>
	</tr>";
	}
}
$msg .= "
   </table>
  </td>
  <td width=\"50%\">&nbsp;</td>
 </tr>
</table><br>
<table class=\"bdrall\" cellpadding=\"0\" width=\"100%\">
<tr>
 <td>Dato</td><td>Ordre nr</td>
 <td>Stk.</td><td>Varenr</td><td>Varetekst</td>
 <td>Stk. Pris</td><td>Rabat i %</td><td>Total Pris</td>
</tr>
";
$res = mysql_query($sql,$link);
$msg .= "<!--
SQL Query: $sql
SQL Error: ". mysql_error($link) . "
-->";
$tot = 0.0;
$oid=0;
while($r = mysql_fetch_assoc($res))
{
if($oid != 0) {
  if($oid != $r["tilbud_nr"]) {
    $oid = $r["tilbud_nr"];
	$msg .= "
<tr>
 <td colspan=\"8\">&nbsp;</td>
</tr>";
  }
} else {
  $oid = $r["tilbud_nr"];
}
$time = strtotime($r["dato"]);
$stk = $r["stk"];
$rabat = 1 - ($r["rabat"] / 100);
$total = ($r["pris"] * $stk) * $rabat;
$tot += $total;
$msg .= "
<tr>
 <td class=\"bdrb\">".strftime("%d %b %Y",$time)."</td>
 <td class=\"bdrbr\">".$r["tilbud_nr"]."</td>
 <td class=\"bdrbr\">".$stk."</td>
 <td class=\"bdrb\">".$r["vare_nr"]."</td>
 <td class=\"bdrbr\">".$r["varetekst"]."</td>
 <td class=\"bdrbr\" align=\"right\">".number_format($r["pris"],"2",",",".")."</td>
 <td class=\"bdrbr\" align=\"center\">".number_format($r["rabat"],"2",",",".")."%</td>
 <td class=\"bdrbr\" align=\"right\">".number_format($total,"2",",",".")."</td>
</tr>
";
}
$msg .="<tr>
 <td colspan=\"8\">&nbsp;</td>
</tr>
<tr>
 <td colspan=\"5\">&nbsp;</td>
 <td colspan=\"2\" class=\"bdrb\" align=\"right\">Brutto i alt</td>
 <td class=\"bdrbr\" align=\"right\">". number_format($tot,2,",",".") ."</td>
</tr>
</table>
</td>

<!-- Right buffer zone -->
<td width=\"15\">&nbsp;</td>

</tr>
</body>
</html>
";
$salg = user_m($usr,$link);

$custom = new htmlMimeMail();

$custom->setReturnPath($salg);
$custom->setFrom('"Helhed" <'.$salg.'>');
$custom->setSubject($msub);

$custom->setHtml($msg);
$x[] = $salg;
$custom->send($x,'smtp');
global $head;
echo $head;
?>
<res>
 <success><?php echo unicode("Listen er nu på vej til dig."); ?></success>
</res>
