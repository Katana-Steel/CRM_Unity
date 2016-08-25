<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_stat_list.php is part of Helhed Client.

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
global $head,$rpath;
$sid = $_POST['sid'];
$to = $_POST['to'];
$from = $_POST['from'];
$link = dbcon();
if($sid != $usr) {
	if(getUserAccess($usr,$link) < 9) {
		echo $head;
?>
<res>
<error><?php echo unicode("Dette skulle faktisk ikke kunne ske,\nmen det gjorer det nu aligevel."); ?></error>
</res>
<?php   return;
	}
}
srand(time());
$uid = md5(uniqid(rand(), true));
$sql = "insert into stat_list set `uid`='$uid',`sid`='$sid',`to`='$to',`from`='$from'";
mysql_query($sql,$link);
mysql_close($link);
echo $head;
?>
<res>
<debug><?php echo $sid ?> <?php echo $from ?> <?php echo $to ?>
<?php echo $sql; ?></debug>
 <page>http://<?php echo $_SERVER['SERVER_NAME'] . $rpath ?>/preview.php?sid=<?php echo $uid; ?></page>
</res>

