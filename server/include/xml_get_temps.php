<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_get_temps.php is part of Helhed Client.

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
$link = dbcon();
if(isset($_POST['id'])) {
 $id = $_POST['id'];
 $sql = "select file from tmp_files where id = $id";
 $res = mysql_query($sql,$link);
 $r = mysql_fetch_row($res);
 $out = file("/var/ftp/oj/tmp/".$r[0]);
 mysql_free_result($res);
 foreach($out as $line) echo unicode($line);
} else {
 global $head;
 $sql = "select title,id from tmp_files where user='$usr'";
 $res = mysql_query($sql,$link);
 echo $head;
 if(mysql_num_rows($res) == 0) {
?>
<res>
 <error>Du har ingen gemte</error>
</res>
<?php
 } else {
?>
<tmp_list>
<?php
  while($r = mysql_fetch_row($res)) {
?>
 <tmp>
  <ttitle><?php echo $r[0]; ?></ttitle>
  <tid><?php echo $r[1]; ?></tid>
 </tmp>
<?php
  }
?>
</tmp_list>
<?php
 }
}
mysql_close($link);
?>
