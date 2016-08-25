<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_admin.php is part of Helhed Client.

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
$type = $_POST['type'];
$link = dbcon();
if(getUserAccess($usr,$link) < 10) $type = "";
switch($type) {
case 'user':
  include('include/xml_admin_user.php');
  break;
case 'mailrule':
  include('include/xml_admin_mailrule.php');
  break;
case 'update':
  include('include/xml_admin_update.php');
  break;
default:
  global $cid, $err;
  $err = "Administations funktionen du valgte,\ner ikke underst\370ttet af denne server.\n\n";
  $cid = 0;
  break;
}
mysql_close($link);
return;
?>
