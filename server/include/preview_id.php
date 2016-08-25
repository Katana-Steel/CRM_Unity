<?php
/**************************************************************************
    This file: ../web/helhed/include/preview_id.php is part of Helhed Client.

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
$cid = $_GET['id'];
$sql = "select * from preview where id='$cid'";
$res = mysql_query($sql,$link);
$rows = mysql_num_rows($res);
if($rows != 0) {
$r = mysql_fetch_assoc($res);
$sql = "delete from preview where id='$cid'";
mysql_query($sql,$link);
$sql = "select * from K_notat where tilbud_nr = ". $r['onr'];
$res = mysql_query($sql,$link);
$r = mysql_fetch_assoc($res);
printp($r['tilbud_nr'],$r['tilbud_type'],$r['k_id'],$link);
mysql_close($link);
exit(0);
}
?>
