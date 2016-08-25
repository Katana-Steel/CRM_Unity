<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_get_mails.php is part of Helhed Server.

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
  $sql = "select mail from used_mails where user='$usr' order by times desc limit 15";
  $res = mysql_query($sql, $link);
  echo $head;
  if(mysql_num_rows($res) == 0) {
?>
<res>
  <success>Der blev ikke fundet nogle mails</success>
</res>
<? } else { ?>
<mail_list>
<? if(isset($_POST['nid'])) echo "<nid>".$_POST['nid']."</nid>\n";
while($r = mysql_fetch_row($res)) { ?>
  <mail><?= $r[0] ?></mail>
<? } ?>
</mail_list>
<? } ?>
