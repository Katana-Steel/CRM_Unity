<?php
/**************************************************************************
    This file: ../web/helhed/preview.php is part of Helhed Client.

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
$rpath = $_SERVER['SCRIPT_NAME'];
$lpos = strrpos($rpath, '/');
$rpath = substr($rpath, 0,$lpos);
include('include/include.php');
// Excel begin of file header
$link = dbcon();
if(isset($_GET['xls'])) {
  include('include/preview_xls.php');
} else if(isset($_GET['sid'])) {
  include('include/preview_sid.php');
} else if(isset($_GET['hid'])) {
  include('include/preview_hid.php');
} else if(isset($_GET['id'])) {
  include('include/preview_id.php');
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Forevisning</title>
<style>
td {
	color: #FF0000;
	font-family: Verdana, Arial, Helvetica, sans-serif;
	font-size: 16pt;
	font-weight: bold;
}
</style>
</head>
<body>
<table align="center">
<tr>
<td>Der findes intet gemt under dette ID</td>
</tr>
</table>
</body>
</html>
<?php mysql_close($link); ?>
