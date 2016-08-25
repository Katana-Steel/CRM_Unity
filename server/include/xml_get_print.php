<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_get_print.php is part of Helhed Client.

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
global $cid, $err, $head, $rpath;
$sql = "select * from K_notat where tilbud_nr = $nr";
$res = mysql_query($sql,$link);
if(mysql_num_rows($res) == 0) {
  $cid = 0; $err = "Der er ingen journal på\nnummeret: $nr";
  return;
}
srand(time());
$uid = md5(uniqid(rand(), true));
$sql = "insert into preview set id='$uid',onr=$nr";
mysql_query($sql,$link);
echo $head;
?>
<res>
 <page>http://<?php echo $_SERVER['SERVER_NAME'] . $rpath; ?>/preview.php?id=<?php echo $uid; ?></page>
</res>
