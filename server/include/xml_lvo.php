<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_lvo.php is part of Helhed Client.

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
if(getUserAccess($usr,$link) < 10) $type = "";
switch($type) {
case 'sag_insert':
  include('include/xml_lvo_sinsert.php');
  break;
case 'sag_run':
  include('include/xml_lvo_srun.php');
  break;
case 'g_update':
  include('include/xml_lvo_gupdate.php');
  break;
case 'g_run':
  include('include/xml_lvo_grun.php');
  break;
case 'g_delete':
  include('include/xml_lvo_gdelete.php');
  break;
default:
  global $cid, $err;
  $err = "Opdateringen af database udfra den\nfil type du valgte,\ner ikke understøttet af denne server.\n\n";
  $cid = 0;
  break;
}
mysql_close($link);
return;
?>
