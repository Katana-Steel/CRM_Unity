<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_admin_mailrule.php is part of Helhed Server.

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
switch($_POST['f']) {
case 'get':
 $sql = "select * from mail_rules order by id";
 $res = mysql_query($sql,$link);
 if(mysql_num_rows($res) != 0) {
  echo $head;
?>
<res>
<?
  while($r = mysql_fetch_assoc($res)) { 
?>
 <rule>
  <id><?= $r['id'] ?></id>
  <active><?= $r['active'] ?></active>
  <type><?= unicode($r['type']) ?></type>
  <cond><?= unicode($r['conditions']) ?></cond>
  <test><?= unicode($r['test_var']) ?></test>
  <list><?= unicode($r['maillist']) ?></list>
 </rule>
<? 
  }
 } 
?>
</res>
<? 
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
