<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_admin_user.php is part of Helhed Server.

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
if(strstr($_SERVER["PHP_SELF"],"xml_admin_user.php") === false) {
} else {
$include_path = ini_get('include_path');
ini_set('include_path',"../:".$include_path);
include_once('include.php');
ini_set('include_path',$include_path);
$link = dbcon();
}
switch($_POST['f']) {
case 'get':
 $sql = "select * from Bruger order by enavn";
 $res = mysql_query($sql,$link);
 if(mysql_num_rows($res) != 0) {
  echo $head;
?>
<res>
<?
  while($r = mysql_fetch_assoc($res)) { 
?>
 <user>
  <username><?= unicode($r['brugernavn']) ?></username>
  <tokanr><?= unicode($r['tokalvl']) ?></tokanr>
  <usrnr><?= unicode($r['brugernr']) ?></usrnr>
  <fname><?= unicode($r['fnavn']) ?></fname>
  <lname><?= unicode($r['enavn']) ?></lname>
  <mobil><?= unicode($r['mobil']) ?></mobil>
  <email><?= unicode($r['mail']) ?></email>
  <tlf><?= unicode($r['tlf']) ?></tlf>
 </user>
<? 
  }
 } 
?>
</res>
<? 
 break;
case 'edit':
 $sql = "select * from Bruger where brugernavn='".funicode($_POST['user'])."'";
 $res = mysql_query($sql,$link);
 if(mysql_num_rows($res) != 0) {
  $do = true;
  if($r['brugernr'] == funicode($_POST['usrnr']))
   if($r['tokalvl'] == funicode($_POST['tokanr']))
    if($r['fnavn'] == funicode($_POST['fname']))
     if($r['enavn'] == funicode($_POST['lname']))
      if($r['mobil'] == funicode($_POST['mobil']))
       if($r['mail'] == funicode($_POST['email']))
        if($r['tlf'] == funicode($_POST['tlf']))
	     $do = false;

  if($do) {
  	$sql  = "update Bruger set ";
	if(isset($_POST['pass']))
     $sql .= "pass='".crypt(funicode($_POST['pass']))."',";
	$sql .= "brugernr=".funicode($_POST['usrnr']).",";
	$sql .= "tokalvl=".funicode($_POST['tokanr']).",";
	$sql .= "fnavn='".funicode($_POST['fname'])."',";
	$sql .= "enavn='".funicode($_POST['lname'])."',";
	$sql .= "mobil='".funicode($_POST['mobil'])."',";
	$sql .= "mail='".funicode($_POST['email'])."',";
	$sql .= "tlf='".funicode($_POST['tlf'])."' ";
	$sql .= "where brugernavn='".funicode($_POST['user'])."'";
	mysql_query($sql,$link);
	$sqlerr = mysql_error($link);
    echo $head;
?>
<res>
 <sql_error><?= $sqlerr ?></sql_error>
 <success><?= unicode("Brugeren er nu rettet.") ?></success>
</res>
<? 
  } else {
   echo $head;
?>
<res>
 <error><?= unicode("Brugeren er ikke blevet rettet.") ?></error>
</res>
<? 
  }
 } else {
  echo $head;
?>
<res>
 <error><?= unicode("Syntax error.") ?></error>
</res>
<? 
 }
 break;
case 'create':
 $sql = "select * from Bruger where brugernavn='".funicode($_POST['user'])."'";
 $res = mysql_query($sql,$link);
 if(mysql_num_rows($res) != 0) {
  echo $head;
?>
<res>
 <error>Du kan ikke oprette en bruger, med et 
brugernavn der eksister i forvejen</error>
</res>
<?
 } else {
  $sql  = "insert into Bruger set ";
  $sql .= "brugernavn='".funicode($_POST['user'])."',";
  $sql .= "pass='".crypt(funicode($_POST['pass']))."',";
  $sql .= "brugernr=".funicode($_POST['usrnr']).",";
  $sql .= "tokalvl=".funicode($_POST['tokanr']).",";
  $sql .= "fnavn='".funicode($_POST['fname'])."',";
  $sql .= "enavn='".funicode($_POST['lname'])."',";
  $sql .= "mobil='".funicode($_POST['mobil'])."',";
  $sql .= "mail='".funicode($_POST['email'])."',";
  $sql .= "tlf='".funicode($_POST['tlf'])."' ";
  mysql_query($sql,$link);
  echo $head;
?>
<res>
 <sql_error><?= mysql_error($link); ?></sql_error>
 <success><?= unicode("Bruger: '".funicode($_POST['user'])."' er nu oprettet.") ?></success>
</res>
<? 
 }
 break;
case 'delete':
 $sql = "select * from Bruger where brugernavn='".funicode($_POST['user'])."'";
 $res = mysql_query($sql,$link);
 if(mysql_num_rows($res) == 0) {
  echo $head;
?>
<res>
 <error>Du kan ikke slette en bruger der ikke findes</error>
</res>
<?
 } else {
 $usr = funicode($_POST['user']);
 $rps = funicode($_POST['replace']);
 $sql = "delete from Act_Conn where user='$usr'";
 mysql_query($sql,$link);
 $sql = "delete from Bruger where brugernavn='$usr'";
 mysql_query($sql,$link);
 $sql = "delete from used_mails where user='$usr'";
 mysql_query($sql,$link);
 $sql = "update K_notat set saelger_id='$rps' where saelger_id='$usr'";
 mysql_query($sql,$link);
 $sql = "update tmp_files set user='$rps' where user='$usr'";
 mysql_query($sql,$link);
 $sql = "select mail from Bruger where brugernavn='$rps'";
 $r = mysql_fetch_row(mysql_query($sql,$link));
 $sql = "select fnavn,enavn from Bruger where brugernavn='$rps'";
 $n = mysql_fetch_row(mysql_query($sql,$link));
 $sub = "Overdragelse af bruger fra Helheds modulet";
 $msg = "<html>
 <head>
  <title>$sub</title>
 </head>
 <body>
  <table style=\"border: 0px;\">
   <tr><td align=\"left\">Hej ".$n[0]." ".$n[1].",</td></tr>
   <tr><td align=\"center\">&nbsp;</td></tr>
   <tr><td align=\"center\">Du har nu ansvaret for alt det som bruger: '$usr' har lavet.</td></tr>
   <tr><td align=\"center\">&nbsp;</td></tr>
   <tr><td align=\"right\">Venlig hilsen<br>Helheds modulets Administration</td></tr>
  </table>
 </body>
</html>";
$custom = new htmlMimeMail();

$custom->setReturnPath("helhed@keenan.dk");
$custom->setFrom('"Helheds modulet" <helhed@keenan.dk>');
$custom->setSubject($sub);
$custom->setHtml($msg);
$mres = $custom->send($r,'smtp');
 echo $head;
?>
<res>
 <success>Bruger er nu slettet og en mail er blevet
sent til den nye bruger</success>
</res>
<? }
 break;
}
?>
