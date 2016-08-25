<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_admin_mailrule.php is part of Helhed Client.

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
switch($_POST['f']) {
case 'get':
 $sql = "select * from mail_rules order by id";
 $res = mysql_query($sql,$link);
 if(mysql_num_rows($res) != 0) {
  echo $head;
?>
<res>
<?php
  while($r = mysql_fetch_assoc($res)) {
?>
 <rule>
  <id><?php echo $r['id']; ?></id>
  <active><?php echo $r['active']; ?></active>
  <type><?php echo unicode($r['type']); ?></type>
  <cond><?php echo unicode($r['conditions']); ?></cond>
  <test><?php echo unicode($r['test_var']); ?></test>
  <list><?php echo unicode($r['maillist']); ?></list>
 </rule>
<?php
  }
?>
</res>
<?php
 }
 break;
case 'update':
 $id = $_POST['id'];
 $act = $_POST['act'];
 $type = funicode($_POST['t']);
 $cond = funicode($_POST['cond']);
 $test = funicode($_POST['test']);
 $list = funicode($_POST['list']);
 if($id == 0) {
  $sql = "insert into mail_rules set ";
 } else {
  $sql = "update mail_rules set ";
 }
 $sql .= "active='".$act."',".
 		 "type='".$type."',".
		 "conditions='".$cond."',".
		 "test_var='".$test."',".
		 "maillist='".$list."'";
 if(($id != 0) and ($list == "")) $sql = "delete from mail_rules where id=".$id;
 else if($id != 0) $sql .= " where id=".$id;
 mysql_query($sql,$link);
 break;
}
?>
