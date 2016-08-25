<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_save_temp.php is part of Helhed Client.

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
$name = $_POST['title'];
$file = $_POST['file'];
$link = dbcon();
$sql = "select * from tmp_files where user='$usr' and title='$name'";
$res = mysql_query($sql,$link);
if(mysql_num_rows($res) != 0) {
echo $head;
?>
<res>
  <success>' <?php echo unicode($name); ?> ' er nu blevet opdateret.</success>
</res>
<?php
mysql_close($link);
return;
}
mysql_free_result($res);
$sql = "insert into tmp_files set user='$usr',title='$name',file='$file'";
mysql_query($sql,$link);
mysql_close($link);
echo $head;
?>
<res>
  <success>' <?php echo unicode($name); ?> ' er nu gemt.</success>
</res>
