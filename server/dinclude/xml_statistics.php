<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_statistics.php is part of Helhed Server.

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

    Copyright 2008, 2009 RenÃ© Kjellerup aka Katana Steel
**************************************************************************/
?>
<?
global $head;
$type = $_POST['type'];
$link = dbcon();
switch($type) {
case 'lukk':
  include('include/xml_stat_akt_tilbud.php');
  break;
case 'tot_salg':
  include('include/xml_stat_totsalg.php');
  break;
case 'multi':
  include('include/xml_stat_sogning.php');
  break;
case 'stklist':
  include('include/xml_stat_stklist.php');
  break;
default:
  global $cid, $err;
  $err = "Statestik funktionen du valgte,\ner ikke understøttet af denne server.\n\n";
  $cid = 0;
  break;
} 
mysql_close($link);
?>
