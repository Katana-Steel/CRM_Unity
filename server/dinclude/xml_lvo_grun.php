<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_lvo_grun.php is part of Helhed Server.

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

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/
?>
<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_lvo_grun.php is part of Helhed Client.

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

    Copyright 2008, 2009, 2010 René Kjellerup aka Katana Steel
**************************************************************************/
?>
<?php
global $head;
$sql = "select * from nye_Sager";
$res = mysql_query($sql,$link);
$num = mysql_num_rows($res);

while($r = mysql_fetch_assoc($res))
{
 if($r["tidx"] == "0") {
  $sql = "insert into ";
 } else {
  $sql = "update ";
 }
 if($r["type"] == "H") {
  // maskiner uses sagnr from nye_Sager for the sorting index number
  if($r['sagnr'] == "") $sort = "9999"; // default add it to the lowest sort group
  else $sort = $r['sagnr'];
  $sql .=  "Maskiner set sort=".$sort.",varenr='".$r["vnr"]."',varetekst='".$r["beskriv"]."',pris=".$r["pris"];
 } else {
  $sql .=  "K_Sager set sagnr='".$r["sagnr"]."',beskriv='".$r["beskriv"]."',pris=".$r["pris"];
 }
 if($r["tidx"] != "0") {
  $sql .= " where id=".$r["tidx"];
 }
 mysql_query($sql,$link);
 $tmp_edit = $sql;
}

$sql = "truncate table nye_Sager";
mysql_query($sql,$link);

echo $head;
?>
<res>
 <l_mysql_string><?php echo $tmp_edit; ?></l_mysql_string>
 <mysql_error><?php echo mysql_error($link); ?></mysql_error>
 <success>Systemet har nu opdateret <?php echo $num; ?> vare</success>
</res>
