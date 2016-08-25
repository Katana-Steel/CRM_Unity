<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_lvo_gdelete.php is part of Helhed Server.

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
$sql  = "delete from ";
if($_POST["type"] == "H") $sql .= " Maskiner ";
else $sql .= " K_Sager ";
$sql .= "where id=".$_POST["id"];
mysql_query($sql,$link);
?>
