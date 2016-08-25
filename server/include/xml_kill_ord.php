<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_kill_ord.php is part of Helhed Client.

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
$id = $_POST['case'];
$cusm = split('[;,]',$_POST['k_email']);
$link = dbcon();
$que = "select tilbud_nr,tilbud_type,tekst,saelger_id from K_notat where notat_id='$id'";
$res = mysql_query($que,$link);
$r = mysql_fetch_row($res);
global $head;
echo $head
?>
<res>
<?php
$tnr = $r[0];
$t = $r[1];
$del = "annulleret";
$que = "update K_notat set ";
if($t != "T") { $que .= "tilbud_type='X',"; $del = "slettet"; }
$que .= "status='I',tekst='<b><i>$del d. ".strftime("%e. %b - %Y",time())."</i></b><br />\n";
if($r[3] != $usr) $que .= "<i>af sælger: \\'$usr\\'</i><br />\n";
$que .= str_replace("'","\\'",$r[2])."' where notat_id=".$id;
?>
<mysql><?php echo str_replace("<","[",str_replace(">","]",$que)); ?></mysql><?php
mysql_query($que,$link);
?>
<myerr><?php echo mysql_error($link); ?></myerr>
<?php
if($t != "T") {
 $que = "update `K-tilbud` set type='X' where tilbud_nr=" . $tnr;
 mysql_query($que,$link);
 $onr = $r[0];
}
$msub = "Ordre nr: $onr er blevet annulleret";
$msg = killordm($onr,$msub,$link);
if($t == "O" || $t == "K") {
defaultMails($cusm, $usr,"X","");
}
$cusm[] = $salg = user_m($usr,$link);
if($salg == "") $salg = "salg@bhsribe.dk";

function filter($v) {
 return(trim($v) != "");
}
$cusm = array_filter($cusm,"filter");
$cusm = array_unique($cusm);
$custom = new htmlMimeMail();

$custom->setReturnPath($salg);
$custom->setFrom('"Helhed" <'.$salg.'>');
$custom->setSubject($msub);

$custom->setHtml($msg);
foreach($cusm as $mail)
{
 if(trim($mail) == "") continue;
 if(isset($x)) unset($x);
 $x[] = $mail;
 $custom->send($x,'smtp');
}
mysql_close($link);
?>
	<success><?php echo $tnr, ?> er nu blevet <?php echo $del; ?> og der er
blevet mail'et til dem der har <?php echo unicode("ønsket"); ?> det.</success>
</res>
