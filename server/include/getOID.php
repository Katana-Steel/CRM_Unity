<?php
/**************************************************************************
    This file: ../web/helhed/include/getOID.php is part of Helhed Client.

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

if ($oid == "")
{
  $que = "select tilbud_nr from `K-tilbud` where (type='$type'";
  if($type == "O") $que .= " or type='X') and (tilbud_nr < 36000000";
  $que .= ") order by tilbud_nr desc limit 1";
  $res = mysql_query($que,$link) or die(mysql_error($link));
  $r[0] = 0;
  $t = mysql_num_rows($res);
  if($t > 0) {
    $r = mysql_fetch_row($res);
    $oid = 1 + $r[0];
  }
}
if($oid == "") {
  switch($type) {
  case 'T':
    $oid = "12000001";
	break;
  case 'O':
    $oid = "24000001";
	break;
  case 'K':
    $oid = "36000001";
	break;
  case 'S':
    $oid = "60000001";
	break;
  case 'A':
    $oid = "48000001";
	break;
  }
}
?>
