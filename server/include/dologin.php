<?php
/**************************************************************************
    This file: ../web/helhed/include/dologin.php is part of Helhed Client.

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

    Copyright 2008, 2009, 2010 René Kjellerup aka Katana Steel
**************************************************************************/

$bruger = strtolower($_POST["user"]);

$pass = $_POST["pass"];

$num = strpos($bruger,";");
if($num !== false)
{
    return;
}
$que = "select brugernavn,pass from Bruger where brugernavn='$bruger'";
$res = mysql_query($que,$link) or die($que ."\n<br>".$link.mysql_error());
if(mysql_num_rows($res) != 0) {
  $row = mysql_fetch_assoc($res);
  $cry = $row["pass"];
  if ( $cry == crypt($pass,$cry) ) {
    global $login,$cid; /* could have been done differently however,
			   what you can't see is the web interface
			   which I've removed as it were hella slow
			   and it also used this funcion for the login. */
     mysql_query("delete from Act_Conn where user='".$bruger."'",$link);
     mysql_query("insert into Act_Conn set valid=1,cid='$cid',user='".$bruger."'",$link);
     $login = true;
  }
}
mysql_free_result($res);
?>
