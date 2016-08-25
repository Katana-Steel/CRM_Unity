<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/dologin.php is part of Helhed Server.

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

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/
?>
<? 
global $app;
global $klogin;
$bruger = strtolower($_POST["user"]);

$pass = $_POST["pass"];

$num = strpos($bruger,";");
if(!($num === false) )
{
	header("Location: http://". $_SERVER["HTTP_HOST"] . $_SERVER["SCRIPT_NAME"] );
}
$link = dbcon();

/* if($klogin) {
  $que = "select `password` from keenan_kunde where kundenr='$bruger'";
  $res = mysql_query($que,$link) or die($que ."\n<br>".$link.mysql_error());
  if(mysql_num_rows($res) != 0) {
  $row = mysql_fetch_row($res);
  $cry = $row[0];
  if($cry == "1234" && $cry == $pass) {
	setcookie("user",$bruger,0,"/",$_SERVER['HTTP_HOST']) or die("unable to set user cookie");
    setcookie("pass",$pass,0,"/",$_SERVER['HTTP_HOST']) or die("unable to set pass cookie");
	header("Location: http://". $_SERVER["HTTP_HOST"] . $_SERVER["SCRIPT_NAME"] . "/newpass" );
  } else if($row["pass"] == crypt($pass,$row[0])) {
	setcookie("user",$bruger,0,"/",$_SERVER['HTTP_HOST']) or die("unable to set user cookie");
    setcookie("pass",$pass,0,"/",$_SERVER['HTTP_HOST']) or die("unable to set pass cookie");
  }
} /* else {  */
$que = "select brugernavn,pass from Bruger where brugernavn='$bruger'";
$res = mysql_query($que,$link) or die($que ."\n<br>".$link.mysql_error());
if(mysql_num_rows($res) != 0) {
$row = mysql_fetch_array($res,MYSQL_BOTH);
$cry = $row["pass"];
if ( strcmp($bruger,$_POST['user']) == 0 && $row["pass"] == crypt($pass,$row["pass"]) ) {
  if($app) {
    global $login,$cid;
	mysql_query("delete from Act_Conn where user='".$bruger."'",$link);
	mysql_query("insert into Act_Conn set valid=1,cid='$cid',user='".$bruger."'",$link);
	$login = true;
  } else {
    setcookie("user",$bruger,0,"/",$_SERVER['HTTP_HOST']) or die("unable to set user cookie");
    setcookie("pass",$pass,0,"/",$_SERVER['HTTP_HOST']) or die("unable to set pass cookie");
  }
}
}
//}
/*echo $row[0] ."\n<br>". $row[1] ."\n<br>";
print_r($_COOKIE);*/
mysql_close($link);
//header("Location: http://". $_SERVER["HTTP_HOST"] . $_SERVER["SCRIPT_NAME"] );
sleep(1);
if(!$app) {
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
</head>
<body bgcolor="#000000">
<? 
echo "<script language=\"JavaScript\">\n";
if ( $cry == crypt($pass,$cry) ) {
echo "alert(\"". $bruger ." is now logged in\");\n";
}
echo "self.location.href = \"". $_SERVER["SCRIPT_NAME"]."\";\n";
echo "</script>";
?>
</body>
</html>
<? } ?>
