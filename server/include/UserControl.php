<?php
/**************************************************************************
    This file: ../web/helhed/include/UserControl.php is part of Helhed Client.

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

function user($str,$link)
{
$que = "select fnavn,enavn,tlf from Bruger where brugernavn = '$str'";
$res = mysql_query($que,$link);
if(mysql_num_rows($res) == 0) return "Helheds System&nbsp;";
$row = mysql_fetch_row($res);
return $row[0] ." ". $row[1] ."&nbsp;&nbsp;tlf: +45 ". $row[2];
}

function user_m($str, $link)
{
$que = "select mail from Bruger where brugernavn = '$str'";
$res = mysql_query($que,$link);
$row = mysql_fetch_row($res);
return $row[0];
}

function getUserAccess($user,$link)
{
	$que = "select brugernr from Bruger where brugernavn = '".$user."'";
	$res = mysql_query($que,$link) or die(mysql_error());
	$row = mysql_fetch_row($res);
	$bgr = $row[0];
	mysql_free_result($res);
	$ret = $bgr;
	return $ret;
}
?>
