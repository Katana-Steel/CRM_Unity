<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_get_xls.php is part of Helhed Server.

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
srand(time());
$uid = md5(uniqid(rand(), true));
$sql = "insert into multi_search set id='$uid',sql='$save'";
mysql_query($sql,$link);
?>
<res>
 <page>http://80.160.156.42/helhed/preview.php?xls=<?= $uid ?></page>
</res>
