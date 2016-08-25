<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_reenable.php is part of Helhed Client.

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

    Copyright 2008, 2009 RenÃ© Kjellerup aka Katana Steel
**************************************************************************/
?>
<?php
$id = $_POST['case'];
$link = dbcon();
$que = "select tilbud_nr,tilbud_type,tekst,saelger_id from K_notat where notat_id='$id'";
$res = mysql_query($que,$link);
$r = mysql_fetch_row($res);
global $head;
echo $head
?>
<res>
<?php
$tnr = $r[0];
$t = $r[1];
$del = "Genaktiveret";
$que = "update K_notat set status='A',tekst='<b><i>$del d. ".strftime("%e. %b - %Y",time())."</i></b><br />\n";
if($r[3] != $usr) $que .= "<i>af sælger: \\'$usr\\'</i><br />\n";
$que .= str_replace("'","\\'",$r[2])."' where notat_id=".$id;
?>
<mysql><?php echo str_replace("<","[",str_replace(">","]",$que)); ?></mysql>
<?php
mysql_query($que,$link);
mysql_free_result($res);
?>
<mysql_error><?php echo mysql_error($link);; ?></mysql_error>
<success>Ordre nr: '<?php echo $r[0]; ?>' er blevet gyldigt igen.</success>
</res>
