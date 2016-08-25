<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_rma.php is part of Helhed Client.

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
$type = $_POST['f'];
$link = dbcon();
if(getUserAccess($usr,$link) < 4) $type = "";
switch($type) {
case 'get all':
  include('dinclude/xml_rma_getall.php');
  break;
default:
  global $cid, $err;
  $err = "\n\n";
  $cid = 0;
  break;
}
mysql_close($link);
return;
?>
