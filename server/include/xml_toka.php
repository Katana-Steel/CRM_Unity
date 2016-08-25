<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_toka.php is part of Helhed Client.

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
global $head;
$link = dbcon();
echo $head;
echo "<toka>\n";
$sql = "select * from `K_notat` where tilbud_nr=$nr order by notat_id";
$res = mysql_query($sql,$link);
$r = mysql_fetch_assoc($res);
$salg_id = $r["saelger_id"];
?>
 <from><?php echo $r["notat_id"]; ?></from>
 <int_msg><?php echo unicode($r['internal_msg']); ?></int_msg>
<?php
$sql = "select * from `K-tilbud` where tilbud_nr=$nr order by linie_nr";
$res = mysql_query($sql,$link);
while($r = mysql_fetch_assoc($res)) {
   if($r["stk"] > 0) {
?>
 <salg>
  <stk><?php echo $r["stk"]; ?></stk>
<?php } else { ?>
 <byt>
  <stk><?php echo -1*$r["stk"]; ?></stk>
<?php } ?>
  <nr><?php echo unicode($r["vare_nr"]); ?></nr>
  <txt><?php echo unicode($r["varetekst"]); ?></txt>
  <pris><?php echo $r["pris"]; ?></pris>
<?php
	if($r["stk"] > 0) {
?>
  <rab><?php echo $r["rabat"]; ?></rab>
 </salg>
<?php } else { ?>
 </byt>
<?php }
}
$res = mysql_query($sql,$link);
$r = mysql_fetch_assoc($res);
if($_POST['type'] == 'A') {
?>
 <bemark><?php echo unicode("<b>Vdr. Ordre nr: $nr</b>\n<i><b>af Sælger: ".$salg_id."</b></i>\n\n".$r["bemaerk"]); ?></bemark>
<?php } else { ?>
 <bemark><?php echo unicode($r["bemaerk"]); ?></bemark>
<?php } ?>
 <reknr><?php echo $r["reknr"]; ?></reknr>
<?php
$levbet = split(";",$r["lev_kunde"]);
?>
 <levb><?php echo unicode($levbet[0]); ?></levb>
 <betb><?php echo unicode($levbet[1]); ?></betb>
<?php
if($r["lev"] == 1) {
 $sql = "select * from lev_addr where oid=$nr";
 $res = mysql_query($sql,$link);
 $r = mysql_fetch_assoc($res);
?>
 <lev_navn><?php echo $r["navn"]; ?></lev_navn>
 <lev_att><?php echo $r["att"]; ?></lev_att>
 <lev_adr><?php echo $r["adresse1"]; ?></lev_adr>
 <lev_post><?php echo $r["post"]; ?></lev_post>
 <lev_by><?php echo $r["by"]; ?></lev_by>
<?php
}
?>
<type><?php
switch($_POST['type']) {
  case 'T':
?>0<?php
	break;
  case 'O':
?>1<?php
	break;
  case 'K':
?>2<?php
	break;
  case 'A':
?>3<?php
	break;
  case 'S':
?>4<?php
	break;
}
?></type>
</toka>
