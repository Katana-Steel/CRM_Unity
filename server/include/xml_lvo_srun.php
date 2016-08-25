<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_lvo_srun.php is part of Helhed Client.

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

$sql = "truncate table K_Sager";
mysql_query($sql,$link);

$sql  = "insert into K_Sager (sagnr,beskriv,pris) ";
$sql .= "select nye_Sager.sagnr,nye_Sager.beskriv,nye_Sager.pris from nye_Sager";
mysql_query($sql,$link);

$sql = "truncate table nye_Sager";
mysql_query($sql,$link);

$sql = "select * from K_Sager";
$res = mysql_query($sql,$link);
$num = mysql_num_rows($res);
mysql_free_result($res);

echo $head;
?>
<res>
 <mysql_error><?php echo mysql_error($link); ?></mysql_error>
 <success>Der er nu <?php echo $num; ?> Sager i systemet</success>
</res>
