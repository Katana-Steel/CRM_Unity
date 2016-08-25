<?php
/**************************************************************************
    This file: ../web/helhed/include/printm.php is part of Helhed Client.

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
global $cid;
$que = "select reknr from `K-tilbud` where tilbud_nr=$id";
$p = mysql_query($que,$link);
$r = mysql_fetch_row($p);
$rek = $r[0];
$que = "select saelger_id from K_notat where tilbud_nr=$id and titel not like 'sup. mail%'";
$res = mysql_query($que,$link);
$r = mysql_fetch_row($res);
$sp = user($r[0], $link);
$ret = "
<!-- $id
$type
$kid
$cid
$link -->
<html>
<head>
";
$que = "select lev,lev_kunde,bemaerk,dato from `K-tilbud` where tilbud_nr=$id";
$res = mysql_query($que, $link);
$r = mysql_fetch_row($res);
$que = "select * from `lev_addr` where oid=$id";
$res = mysql_query($que, $link);
if(mysql_num_rows($res) != 0) {
 $l = mysql_fetch_assoc($res);
}
list($lev,$beta) = split(';',$r[1]);
$bemark = $r[2];
$dato = $r[3];
switch($type)
{
case 'T':
$ret .= "<title>Tilbud nr. $id</title>\n";
break;
case 'O':
$ret .= "<title>Ordre nr. $id</title>\n";
break;
case 'K':
$ret .= "<title>Konsignation nr. $id</title>\n";
break;
case 'A':
$ret .= "<title>Arbejdskort nr. $id</title>\n";
break;
case 'S':
$ret .= "<title>Salgsm\345l nr. $id</title>\n";
break;
}
global $rpath;
$file = $_SERVER['DOCUMENT_ROOT'] . $rpath . "/style/style.css";
$s = file_get_contents($file);
$ret .= "<style>\n${s}\na {\ncolor:black;\n}</style>\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">".
		"</head>\n<body>\n". (($type == 'S') ? order_head($type,$id,"",$rek) : order_head($type,$id)) ."\n";
$que = "select * from kunde where id = $kid";
$res = mysql_query($que, $link);
$row = mysql_fetch_assoc($res);
$land = $row["land"];
if($type != 'A' && $type != 'S') {
  $cpan = 6;
} else {
  $cpan = 3;
}
$ret .= "
<table width=\"100%\" align=\"center\">
 <tr>
";
if($type == 'A') {
$ret .= "  <td colspan=\"2\" style=\"font-size: 10pt;\"><b>Lavet af:</b>". $sp ."</td>";
} else {
$ret .= "  <td colspan=\"2\" style=\"font-size: 10pt;\"><b>Med venlig hilsen:</b>". $sp ."</td>";
}
$ret .= "
 </tr>
 <tr>
  <td width=\"50%\" align=\"right\">
   <table class=\"bdrall\">
	<tr>
	 <td width=\"70\">Kundenr:</td>
	 <td width=\"200\">".$row["kundenr"]."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $row["firma"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $row["navn"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $row["adresse"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $row["post"] ." ". $row["by"] ."</td>
	</tr>";
if($row["EAN_SE"] != "") {
	if(strtolower($row["land"]) == "danmark") {
$ret .= "
	<tr>
	 <td>EAN</td>
	 <td>". $row["EAN_SE"] ."</td>
	</tr>";
	} else {
$ret .= "
	<tr>
	 <td></td>
	 <td>". $row["land"] ."</td>
	</tr>
	<tr>
	 <td></td>
	 <td>". $row["EAN_SE"] ."</td>
	</tr>";
	}
}
$ret .= "
	<tr>
	 <td>Tlf. / fax / mobil:</td>
	 <td>". $row["tlf"] ." / ". $row["fax"] ." / ".$row["mobil"]."</td>
	</tr>
	<tr>
	 <td>CVR- nr.:</td>
	 <td></td>
	</tr>
	<tr>
	 <td colspan=\"2\">";
if($type != 'K') {
$ret .= "<b>K&Oslash;BER</b>";
} else {
$ret .= "<b>KONSIGNATAR</b>";
}
$ret .= "</td>
	</tr>
   </table>
  </td>
  <td width=\"50%\">
   <table class=\"bdrall\">
	<tr>
	 <td width=\"70\">&nbsp;</td>
	 <td width=\"200\">". $l["navn"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $l["att"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $l["adresse1"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $l["adresse2"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>". $l["post"] ." ". $l["by"] ."</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>&nbsp;</td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>&nbsp;<br />&nbsp;</td>
	</tr>
	<tr>
	 <td colspan=\"2\"><b>LEVERINGSADRESSE</b></td>
	</tr>
   </table>
  </td>
 </tr>
</table><br>
<table class=\"bdrall\" cellpadding=\"0\" width=\"100%\">
<tr>
<td class=\"bdrb\" colspan=\"$cpan\">
 ";
$time = strtotime($dato);
if ($type == "S") {
 $w = mysql_query("select value from calc where tnr=$id",$link);
 $b = mysql_fetch_row($w);
 $t = split(";",$b[0]);
 $time = strtotime($t[0]) . ";". strtotime($t[1]);
 mysql_free_result($w);
}
$ret .= info_text($type,$time) ."
</td>
</tr>";
if($type == 'S') {
 $w = mysql_query("select internal_msg from K_notat where tilbud_nr=$id and titel not like 'sup. mail%'",$link);
 $b = mysql_fetch_row($w);
 $msg = str_replace("\n","<br />\n",$b[0]);
 mysql_free_result($w);
$ret .= "
<tr>
<td class=\"bdrb\" colspan=\"$cpan\">
$msg
</td>
</tr>
";
}
$ret .= "
<tr>
<td>Stk.</td><td>Varenr</td><td>Varetekst</td>\n";
if($type != 'A' && $type != 'S') {
$ret .= "<td>Stk. Pris</td><td>Rabat i %</td><td>Total Pris</td>\n";
}
$ret .= "</tr>
";
$que = "select * from `K-tilbud` where tilbud_nr = $id and stk > 0 order by linie_nr";
$res = mysql_query($que,$link);
$tot = 0;
while($row = mysql_fetch_assoc($res)) {
$stk = $row["stk"];
  $rabat = 1 - ($row["rabat"] / 100);
  $total = ($row["pris"] * $stk) * $rabat;
  $tot += $total;
$ret .= "
<tr>
<td class=\"bdrbr\">
$stk
</td>
<td class=\"bdrb\">
".$row["vare_nr"] ."
</td>
<td class=\"bdrbr\">
". $row["varetekst"] ."
</td>
";
if($type != 'A' && $type != 'S') {
$ret .= "<td class=\"bdrbr\" align=\"right\">
". number_format($row["pris"],2,",",".") ."
</td>
<td align=\"center\" class=\"bdrbr\">
". number_format($row["rabat"],2,",",".") ."
</td>
<td align=\"right\" class=\"bdrbr\">
". number_format($total,2,",",".") ."
</td>
";
}
$ret .= "</tr>
";
}
if($type != 'A' && $type != 'S') {
$ret .="<tr>
<td colspan=\"3\">&nbsp;</td>
<td colspan=\"2\" class=\"bdrb\" align=\"right\">Brutto i alt</td>
<td class=\"bdrbr\" align=\"right\">". number_format($tot,2,",",".") ."</td>
</tr>";
}
$ret .= "<tr>
<td class=\"bdrb\" colspan=\"$cpan\">&nbsp;</td>
</tr>
<tr>
<td colspan=\"$cpan\">";
if($type != 'S') {
 if($type == 'K') {
$ret .= "til udstilling/videresalg.";
 } else {
$ret .= "<b>I bytte</b>";
 }
}
$ret .= "</td>
</tr>
";
if($type != 'K' && $type != "S") {
$ret .= "<tr>
<td>Stk.</td><td>Varenr</td><td>Varetekst</td>
";
if($type != 'A') {
$ret .= "<td>Stk. Pris</td><td>&nbsp;</td><td>Total Pris</td>
";
}
$ret .= "</tr>
";
$que = "select * from `K-tilbud` where tilbud_nr = $id and stk < 0 order by linie_nr";
$res = mysql_query($que,$link);
$tmp = $tot;
while($row = mysql_fetch_assoc($res)) {
  $rabat = 1 - ($row["rabat"] / 100);
  $stk = $row["stk"] * -1;
  $total = ($row["pris"] * $stk) * $rabat;
  $tot -= $total;
$ret .= "
<tr>
<td class=\"bdrbr\">
$stk
</td>
<td class=\"bdrb\">
".  $row["vare_nr"] ."
</td>
<td class=\"bdrbr\">
". $row["varetekst"] ."
</td>";
if($type != 'A') {
$ret .= "<td class=\"bdrbr\" align=\"right\">
". number_format($row["pris"],2,",",".") ."
</td>
<td align=\"center\" class=\"bdrbr\">
". number_format($row["rabat"],2,",",".") ."
</td>
<td align=\"right\" class=\"bdrbr\">
". number_format($total,2,",",".") ."
</td>";
}
$ret .= "</tr>
";
}
}
if($type != 'A' && $type != 'S') {
$ret .= "<tr>
<td colspan=\"3\">&nbsp;</td>
<td colspan=\"2\" class=\"bdrb\" align=\"right\">Bytte i alt</td>
<td class=\"bdrbr\" align=\"right\">". number_format($tmp-$tot,2,",",".") ."</td>
</tr>
<tr>
<td class=\"bdrb\" colspan=\"$cpan\">&nbsp;</td>
</tr>
<tr>
<td colspan=\"4\">&nbsp;</td>
<td class=\"bdrbr\">
I alt
</td>
<td align=\"right\" class=\"bdrbr\">
". number_format(($tot),2,",",".") ."
</td>
</tr>";
if($land == "" || strtolower($land) == "danmark" || strtolower($land) == "dk") {
$ret .= "
<tr>
<td colspan=\"4\">&nbsp;</td>
<td class=\"bdrbr\">
Moms
</td>
<td align=\"right\" class=\"bdrbr\">
". number_format(($tot*.25),2,",",".") ."
</td>
</tr>
<tr>
<td colspan=\"4\">&nbsp;</td>
<td class=\"bdrbr\">
I alt incl. moms
</td>
<td align=\"right\" class=\"bdrbr\">
". number_format(($tot*1.25),2,",",".") ."
</td>
</tr>";
}
$ret .= "
<tr>
<td colspan=\"6\">
<b>Betaling</b>:<br />
". str_replace("\n","<br />\n",$beta) ."
</td>
</tr>
";
}
/*
// all this below is part of a requested feature which changed requirements
// nearly each time a suggestion to solve it was presented to the requester
// and as such there are remnants of it almost everywhere. I'm leaving them
// there as the client has full support of the feature and it's was only its
// use which were in question.
if($type == 'S') {
 $w = mysql_query("select internal_msg from K_notat where tilbud_nr=$id and titel not like 'sup. mail%'",$link);
 $b = mysql_fetch_row($w);
 $msg = str_replace("\n","<br />\n",$b[0]);
 mysql_free_result($w);
$ret .= "<tr>
<td colspan=\"$cpan\"><b>Markedting:</b></td>
</tr>
<tr>
<td class=\"bdrb\" colspan=\"$cpan\">
 En fast markedtings tekst...<br />
 $msg
</td>
</tr>
";
} */
$ret .= "<tr>
<td colspan=\"$cpan\">";
if($type != 'S') {
$ret .= "
<b>Levering</b>: ". str_replace("\n","<br />\n",$lev) ."<br />";
}
$ret .= "
<b>Bem&aelig;rkning</b>:<br />
". str_replace("\r","",str_replace("\n","<br />\n",$bemark)) ."
</td>
</tr>
".page_bottom();
?>
