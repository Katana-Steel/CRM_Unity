<?php
/**************************************************************************
    This file: ../web/helhed/app/index.php is part of Helhed Client.

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
  $str = $_SERVER['PHP_SELF'];
  $idx = strrpos($str,"/");
  $rhost = $_SERVER['REMOTE_ADDR'];
  $val1 = $_SERVER['SERVER_ADDR'];
  $v1l = strlen($val1);
  $isLocal = false;
  $val2 = $_SERVER['SERVER_ADDR'];
  $v12 = strlen($val2);
  if($val2 == "127.0.0.1") $isLocal = true;
  if(substr($val2,0,3) == "10.") $isLocal = true;
  if(substr($val2,0,7) == "172.16.") $isLocal = true;
  if(substr($val2,0,8) == "169.254.") $isLocal = true;
  if(substr($val2,0,8) == "192.168.") $isLocal = true;

  $t = strlen($rhost);
  $ok = false;
  $len = ($vl1 > $t) ? $t : $v1l;
  if( strncmp($rhost,$val1,$len) == 0) $ok = true;
  else if ($isLocal) { $ok = true; }
  if($ok)  header("Location: http://" . $_SERVER['HTTP_HOST']. substr($str,0,$idx)."/install.htm");
  else header("HTTP/1.0 403 Forbidden: ");
?>
