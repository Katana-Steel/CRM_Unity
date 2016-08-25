<?php
/**************************************************************************
    This file: ../web/helhed/include/chk_cid.php is part of Helhed Client.

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

$link = dbcon();
$res = mysql_query("select valid,user from Act_Conn where cid='$cid'",$link);
$usr;
if(mysql_num_rows($res) > 0) {
	$r = mysql_fetch_assoc($res);
	$usr = $r['user'];
	if($r['valid'] != 1) {
		$cid = 0;
		$usr = "";
	}
} else {
	$cid = 0;
	$usr = "";
}
mysql_free_result($res);
mysql_close($link);
?>
