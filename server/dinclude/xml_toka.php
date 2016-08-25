<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_toka.php is part of Helhed Server.

    Helhed Server is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009 RenÃ© Kjellerup aka Katana Steel
**************************************************************************/
?>
<?
global $head;
$link = dbcon();
echo $head;
echo "<toka>\n";
$sql = "select * from `K_notat` where tilbud_nr=$nr order by notat_id";
$res = mysql_query($sql,$link);
$r = mysql_fetch_assoc($res);
$salg_id = $r["saelger_id"];
?>
 <from><?= $r["notat_id"] ?></from>
 <int_msg><?= unicode($r['internal_msg']) ?></int_msg>
<?
$sql = "select * from `K-tilbud` where tilbud_nr=$nr order by linie_nr";
$res = mysql_query($sql,$link);
while($r = mysql_fetch_assoc($res)) {
   if($r["stk"] > 0) {
?>
 <salg>
  <stk><?= $r["stk"] ?></stk>
<? } else { ?>
 <byt>
  <stk><?= -1*$r["stk"] ?></stk>
<? } ?>
  <nr><?= unicode($r["vare_nr"]) ?></nr>
  <txt><?= unicode($r["varetekst"]) ?></txt>
  <pris><?= $r["pris"] ?></pris>
<?
	if($r["stk"] > 0) {
?>
  <rab><?= $r["rabat"] ?></rab>
 </salg>
<? } else { ?>
 </byt>
<? }
}
$res = mysql_query($sql,$link);
$r = mysql_fetch_assoc($res);
if($_POST['type'] == 'A') {
?>
 <bemark><?= unicode("<b>Vdr. Ordre nr: $nr</b>\n<i><b>af Sælger: ".$salg_id."</b></i>\n\n".$r["bemaerk"]) ?></bemark>
<? } else { ?>
 <bemark><?= unicode($r["bemaerk"]) ?></bemark>
<? } ?>
 <reknr><?= $r["reknr"] ?></reknr>
<?
$levbet = split(";",$r["lev_kunde"]);
?>
 <levb><?= unicode($levbet[0]) ?></levb>
 <betb><?= unicode($levbet[1]) ?></betb>
<? 
if($r["lev"] == 1) {
 $sql = "select * from lev_addr where oid=$nr";
 $res = mysql_query($sql,$link);
 $r = mysql_fetch_assoc($res);
?>
 <lev_navn><?= $r["navn"] ?></lev_navn>
 <lev_att><?= $r["att"] ?></lev_att>
 <lev_adr><?= $r["adresse1"] ?></lev_adr>
 <lev_post><?= $r["post"] ?></lev_post>
 <lev_by><?= $r["by"] ?></lev_by>
<?
}
?>
<type><?
switch($_POST['type']) {
  case 'T':
?>0<?
	break;
  case 'O':
?>1<?
	break;
  case 'K':
?>2<?
	break;
  case 'A':
?>3<?
	break;
  case 'S':
?>4<?
	break;
}
?></type>
</toka>
