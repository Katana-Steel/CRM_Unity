<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_create_jour.php is part of Helhed Server.

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
<?
global $head;
$link = dbcon();
$cid = ($_POST['cust']);
$ulvl = ($_POST['ulvl']);
$nota = ($_POST['nota']);
$ndat = ($_POST['ndat']);
$title = ($_POST['title']);
$sql = "insert into K_notat set titel='$title',dato=NOW(),ndato='$ndat',tekst='$nota',saelger_id='$usr',k_id=$cid,bruger=$ulvl,".
	   "tilbud_type=NULL,status='I'";
echo $head;
?>
<res>
	<debug>
<?
mysql_query($sql,$link);
echo mysql_error($link);
mysql_close($link);
?>
	</debug>
	<success>Journalen er nu oprettet</success>
</res>
