<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_gross_seek.php is part of Helhed Server.

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
    This file: ../web/helhed/include/xml_gross_seek.php is part of Helhed Client.

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
	$vnr = $_POST['vnr'];
	$dd = "";
	if(isset($_POST["Y"])) { $dd = "and sidst_red > '" . $_POST["Y"] . "' "; }
	if(isset($_POST["O"])) { $dd = "and sidst_red < '" . $_POST["O"] . "' "; }

	$sag_q = "select * from K_Sager where sagnr like '$vnr%' or sagnr like '%$vnr' order by sagnr desc";
	$hol_q = "select * from Maskiner where varenr like '%$vnr%' ${dd}order by sort desc, varenr desc, varetekst desc";
	$sag = mysql_query($sag_q,$link);
	$hol = mysql_query($hol_q,$link);
	echo $head;
	if(mysql_num_rows($sag) == 0 && mysql_num_rows($hol) == 0) {
?>
<res>
   <error><?php echo to_win1252("Fandt ingen sager eller varenr der\nder passer til '$vnr'"); ?></error>
</res>
<?php
	} else {
?>
<res>
<?php
		if(mysql_num_rows($sag) != 0) {
			while($r = mysql_fetch_assoc($sag)) {
?>
 <sag>
  <id><?php echo unicode($r["id"]); ?></id>
  <nr><?php echo unicode($r["sagnr"]); ?></nr>
  <txt><?php echo to_win1252($r["beskriv"]); ?></txt>
  <pris><?php echo unicode($r["pris"]); ?></pris>
 </sag>
<?php
			}
		}
		if(mysql_num_rows($hol) != 0) {
			while($r = mysql_fetch_assoc($hol)) {
?>
 <holso>
  <id><?php echo unicode($r["id"]); ?></id>
  <sort><?php echo unicode($r["sort"]); ?></sort>
  <nr><?php echo unicode($r["varenr"]); ?></nr>
  <txt><?php echo to_win1252($r["varetekst"]); ?></txt>
  <pris><?php echo unicode($r["pris"]); ?></pris>
 </holso>
<?php
			}
		}
?>
</res>
<?php
	}
	mysql_free_result($sag);
	mysql_free_result($hol);
	mysql_close($link);
?>
