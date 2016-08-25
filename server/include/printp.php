<?php
/**************************************************************************
    This file: ../web/helhed/include/printp.php is part of Helhed Client.

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
<html>
<head>
<?php
if($pre != "no") {
 $bodyopt = " onclick=\"kill();\"";
}
$que = "select lev from `K-tilbud` where tilbud_nr=$id";
$res = mysql_query($que, $link);
$r = mysql_fetch_row($res);
$que = "select * from `lev_addr` where oid=$id";
$res = mysql_query($que, $link);
if(mysql_num_rows($res) != 0) {
 $l = mysql_fetch_assoc($res);
}
switch($type)
{
case 'T':
?>
<title><?php echo "Tilbud nr. $id"; ?></title>
<?php break;
case 'O':
?>
<title><?php echo "Ordre nr. $id"; ?></title>
<?php break;
case 'K':
?>
<title><?php echo "Konsignation nr. $id"; ?></title>
<?php break;
case 'A':
?>
<title><?php echo "Arbejdskort nr. $id"; ?></title>
<?php break;
case 'S':
?>
<title><?php echo "Salgsm\345l nr. $id"; ?></title>
<?php break;
}
global $rpath;
?>
<link rel="stylesheet" type="text/css" href="style/style.css" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<script language="javascript">
function kill() {
  self.close();
}
</script>
<?php if($type == 'A') { ?>
<style type="text/css">
a {
    color: black;
}
</style>
<?php } ?>
</head>
<body<?php echo $bodyopt; ?>>
<?php
$que = "select reknr from `K-tilbud` where tilbud_nr=$id";
$p = mysql_query($que,$link);
$r = mysql_fetch_row($p);
$rek = "";
if($pre != "no") {
 $rek = $_POST['rekv'];
} else {
 $rek = $r[0];
}
if($type == "S") {
echo order_head($type,$id,"",$rek);
} else {
echo order_head($type,$id,$rek);
}
$que = "select saelger_id from K_notat where tilbud_nr=$id and titel not like 'sup. mail%'";
$res = mysql_query($que,$link);
$r = mysql_fetch_row($res);
$s = user($r[0], $link);
$que = "select * from kunde where id = $kid";
$res = mysql_query($que, $link);
$row = mysql_fetch_assoc($res);
$land = $row["land"];
?>
<table width="100%" align="center">
 <tr>
<?php if($type != 'A') { ?>
  <td colspan="6" style="font-size: 10pt;"><b>Med venlig hilsen:</b><?php echo $s; ?></td>
<?php } else { ?>
  <td colspan="6"><b>Lavet af:</b><?php echo $s; ?></td>
<?php } ?>
 </tr>
 <tr>
  <td width="50%" align="right">
   <table class="bdrall">
	<tr>
	 <td width="70">Kundenr:</td>
	 <td align="left" width="200"><?php echo $row["kundenr"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td align="left"><?php echo $row["firma"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td align="left"><?php echo $row["navn"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td align="left"><?php echo $row["adresse"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td align="left"><?php echo $row["post"]; ?> <?php echo funicode($row["by"]); ?></td>
	</tr>
<?php
if($row["EAN_SE"] != "") {
	if(strtolower($row["land"]) == "danmark" || strtolower($row["land"]) == "dk") {
?>
	<tr>
	 <td>EAN</td>
	 <td><?php echo $row["EAN_SE"]; ?></td>
	</tr>
<?php } else { ?>
	<tr>
	 <td></td>
	 <td><?php echo $row["land"]; ?></td>
	</tr>
	<tr>
	 <td></td>
	 <td><?php echo $row["EAN_SE"]; ?></td>
	</tr>
<?php } } ?>
	<tr style="font-size:8pt">
	 <td>Tlf. / fax / mobil:</td>
	 <td align="left"><?php echo $row["tlf"]; ?> / <?php echo $row["fax"]; ?> / <?php echo $row["mobil"]; ?></td>
	</tr>
	<tr>
	 <td>CVR- nr.:</td>
	 <td></td>
	</tr>
	<tr>
<?php if ($type != 'K') { ?>
	 <td colspan="2"><b>K&Oslash;BER</b></td>
<?php } else { ?>
	 <td colspan="2"><b>KONSIGNATAR</b></td>
<?php } ?>
	</tr>
   </table>
  </td>
  <td width="50%">
   <table class="bdrall">
	<tr>
	 <td width="70">&nbsp;</td>
	 <td width="200"><?php echo $l["navn"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td><?php echo $l["att"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td><?php echo $l["adresse1"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td><?php echo $l["adresse2"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td><?php echo $l["post"]; ?> <?php echo $l["by"]; ?></td>
	</tr>
	<tr>
	 <td>&nbsp;</td>
	 <td>&nbsp;</td>
	</tr>
	<tr style="font-size: 8pt;">
	 <td>&nbsp;</td>
	 <td>&nbsp;&nbsp;</td>
	</tr>
	<tr>
	 <td colspan="2"><b>LEVERINGSADRESSE</b></td>
	</tr>
   </table>
  </td>
 </tr>
</table><br>
<table class="bdrall" cellpadding="0" width="100%">
<?php
if($pre == "no") {
$que = "select bemaerk,lev_kunde,dato from `K-tilbud` where tilbud_nr = $id";
$res = mysql_query($que,$link);
$row = mysql_fetch_assoc($res);
$bemark = $row["bemaerk"];
$dato = $row["dato"];
list($lev,$beta) = split(";",$row["lev_kunde"]);
$que = "select * from `K-tilbud` where tilbud_nr = $id and stk > 0 order by linie_nr";
} else {
$lev = $_POST['lev_b'];
$beta = $_POST['bet_b'];
$bemark = $_POST['tmp_bemark'];
$dato = date("Y-m-d");
$que = "select * from `Skurv` where id=$id and stk > 0 order by line";
}
if($type != "A") {
$time = strtotime($dato);
if($type == "S") {
$w = mysql_query("select value from calc where tnr = $id",$link);
$b = mysql_fetch_row($w);
$t = split(";",$b[0]);
mysql_free_result($w);
$time = strtotime($t[0]).";".strtotime($t[1]);
}
?>
<tr>
 <td colspan="6">&nbsp;</td>
</tr>
<tr>
 <td colspan="6" style="font-size: 9pt;">
  <?php echo info_text($type, $time); ?>
 </td>
</tr>
<tr>
 <td class="bdrb" colspan="6">&nbsp;</td>
</tr>
<?php
 }
 $res = mysql_query($que,$link);
?>
<tr>
<td>Stk.</td><td>Varenr</td><td>Varetekst</td>
<?php if($type != "A" && $type != 'S') { ?><td>Stk. Pris</td><td>Rabat i %</td><td>Total Pris</td><?php } ?>
</tr>
<?php
$tot = 0;
while($row = mysql_fetch_assoc($res))
{
$stk = $row["stk"];
if(type != 'A' && $type != 'S') {
  $rabat = 1 - ($row["rabat"] / 100);
  $total = ($row["pris"] * $stk) * $rabat;
  $tot += $total;
}
?>
<tr>
<td class="bdrbr">
<?php echo $stk; ?>
</td>
<td class="bdrb">
<?php echo ($pre=="no") ? $row["vare_nr"] : $row["vareid"]; ?>
</td>
<td class="bdrbr">
<?php echo ($pre=="no") ? $row["varetekst"] : $row["varetext"]; ?>
</td>
<?php if ($type != 'A' && $type != 'S') { ?>
<td class="bdrbr" align="right">
<?php echo number_format($row["pris"],2,",","."); ?>
</td>
<td align="center" class="bdrbr">
<?php echo number_format($row["rabat"],2,",","."); ?>
</td>
<td align="right" class="bdrbr">
<?php echo number_format($total,2,",","."); ?>
</td>
<?php } ?>
</tr>
<?php }
if($type != 'A' && $type != 'S') {
?>
<tr>
<td colspan="3">&nbsp;</td>
<td colspan="2" class="bdrb" align="right">Brutto i alt</td>
<td class="bdrbr" align="right"><?php echo number_format($tot,2,",","."); ?></td>
</tr>
<?php } ?>
<tr>
<td class="bdrb" colspan="<?php if($type == 'A' || $type == 'S') echo "3"; else echo "6"; ?>">&nbsp;</td>
</tr>
<?php if ($type != 'S') { ?>
<tr>
<?php if ($type != 'K') { ?>
<td colspan="<?php if($type == 'A') echo "3"; else echo "6"; ?>"><b>I bytte</b></td>
<?php } else { ?>
<td colspan="6">til udstilling/videresalg.</td>
<?php } ?>
</tr>
<?php }
if($type != 'K' && $type != 'S') { ?>
<tr>
<td>Stk.</td><td>Varenr</td><td>Varetekst</td>
<?php if($type != "A") { ?>
<td>Stk. Pris</td><td>&nbsp;</td><td>Total Pris</td>
<?php } ?>
</tr>
<?php
if($pre == "no") {
$que = "select * from `K-tilbud` where tilbud_nr = $id and stk < 0 order by linie_nr";
} else {
$que = "select * from `Skurv` where id=$id and stk < 0 order by line";
}
$res = mysql_query($que,$link);
$tmp = $tot;
while($row = mysql_fetch_assoc($res)) {
  $stk = $row["stk"] * -1;
  $total = ($row["pris"] * $stk);
  $tot -= $total;
?>
<tr>
<td class="bdrbr">
<?php echo $stk; ?>
</td>
<td class="bdrb">
<?php echo ($pre=="no") ? $row["vare_nr"] : $row["vareid"]; ?>
</td>
<td class="bdrbr">
<?php echo ($pre=="no") ? $row["varetekst"] : $row["varetext"]; ?>
</td>
<?php if ($type != 'A') { ?>
<td class="bdrbr" align="right">
<?php echo number_format($row["pris"],2,",","."); ?>
</td>
<td align="center" class="bdrbr">
<?php echo number_format($row["rabat"],2,",","."); ?>
</td>
<td align="right" class="bdrbr">
<?php echo number_format($total,2,",","."); ?>
</td>
<?php } ?>
</tr><?
}
} //while
if ($type != 'A' && $type != 'S') { ?>
<tr>
<td colspan="3">&nbsp;</td>
<td colspan="2" class="bdrb" align="right">Bytte i alt</td>
<td class="bdrbr" align="right"><?php echo number_format($tmp-$tot,2,",","."); ?></td>
</tr>
<tr>
<td class="bdrb" colspan="<?php if($type == 'A') echo "3"; else echo "6"; ?>">&nbsp;</td>
</tr>
<tr>
<td colspan="<?php if($type == 'A') echo "3"; else echo "6"; ?>">&nbsp;</td>
</tr>
<tr>
<td colspan="4">&nbsp;</td>
<td class="bdrbr">
I alt
</td>
<td align="right" class="bdrbr">
<?php echo number_format(($tot),2,",","."); ?>
</td>
</tr>
<?php if($land == "" || strtolower($land) == "danmark" || strtolower($land) == "dk") { ?>
<tr>
<td colspan="4">&nbsp;</td>
<td class="bdrbr">
Moms
</td>
<td align="right" class="bdrbr">
<?php echo number_format(($tot*.25),2,",","."); ?>
</td>
</tr>
<tr>
<td colspan="4">&nbsp;</td>
<td class="bdrbr">
I alt incl. moms
</td>
<td align="right" class="bdrbr">
<?php echo number_format(($tot*1.25),2,",","."); ?>
</td>
</tr>
<?php } ?>
<tr>
<td colspan="6">
<b>Betaling</b>:
<?php echo str_replace("\n","<br />\n",$beta); ?>
</td>
</tr>
<?php } ?>
<tr>
<td colspan="<?php if($type == "A" || $type == "S") echo "3"; else echo "6"; ?>" <?php
 if($type == "S") echo "style=\"font-size: 10pt;\""?>>
<?php if($type != 'S') { ?>
<b>Levering</b>: <?php echo str_replace("\n","<br />\n",$lev); ?><br />
<?php } ?>
<?php if($type == 'S') { ?>
<b>Jeres forventninger &amp; tiltag</b>:<br />
<?php } else { ?>
<b>Bem&aelig;rkning</b>:<br />
<?php } ?>
<?php echo str_replace("\n","<br />\n",$bemark); ?>
</td>
</tr>
<?php
// as described shortly in printm() at roughly this spot this
// below was the last suggestion of the printout design of this
// feature and it was never declined nor accepted however I'm
// leaving it as it for the present.
 if($type == "S") {
 $w = mysql_query("select internal_msg from K_notat where tilbud_nr=$id and titel not like 'sup. mail%'",$link);
 $b = mysql_fetch_row($w);
 $msg = $b[0];
 mysql_free_result($w);
?>
 <tr>
  <td class="bdrb" colspan="3">&nbsp;</td>
 </tr>
 <tr>
  <td colspan="3" style="font-size: 10pt;">
   <b>Vores forventninger &amp; tiltag:</b><br />
   <?php echo str_replace("\n","<br />\n   ",$msg); ?>
  </td>
 </tr>
 <tr>
  <td colspan="3">&nbsp;</td>
 </tr>
<?php } ?>
</table><br />
<?php
if(isset($_GET['print'])) {
?>
<script language="javascript">
self.print();
</script>
<?php }
echo page_bottom();
?>
