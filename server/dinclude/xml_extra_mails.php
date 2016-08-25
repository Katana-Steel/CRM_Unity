<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_extra_mails.php is part of Helhed Server.

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

    Copyright 2008, 2009 RenÃ© Kjellerup aka Katana Steel
**************************************************************************/
?>
<?
global $head, $rpath;
$cusm = split("[,;]",$k_mails);
$link = dbcon();
$salg = user_m($usr,$link);
$sql = "select * from K_notat where tilbud_nr=$nr and tilbud_type != 'X' order by dato asc";
$r = mysql_fetch_assoc(mysql_query($sql,$link));
$type = $r['tilbud_type'];
$kid = $r['k_id'];
$bnr = $r['bruger'];
switch($type)
{
case 'T':
$tilb = " Tilbudet";$msub = "Tilbuds nr: $nr";$dc = "tt";$slg = "tilbud";
break;
case 'O':
$tilb = " Ordren";$msub = "Ordre nr: $nr";$dc = "nn";$slg = "ordre";
break;
case 'K':
$tilb = " Konsignationen";$msub = "Konsignations nr: $nr";$dc = "nn";$slg = "konsignation";
break;
case 'A':
$tilb = " Arbejdskortet";$msub = "Arbejdskort nr: $nr";$dc = "tt";$slg = "arbjedskort";
break;
case 'S':
$tilb = " Salgsmålet";$msub = "Salgsmål nr: $nr";$dc = "tt";$slg = "salgsmål";
break;
}
$msg = printm($nr,$type,$kid,$link);

$custom = new htmlMimeMail();

$custom->setReturnPath($salg);
$custom->setFrom('"Brdr. Holst Sørensen A/S" <'.$salg.'>');
$custom->setSubject($msub);

$custom->setTextEncoding('8bit');
$custom->setTextCharset('utf-8');
$custom->setHtmlCharset('utf-8');
$custom->setHeadCharset('utf-8');

$custom->setHtml($msg);
if($type != 'A') {
$custom->addAttachment($custom->getFile($type.".pdf"),"Salgs Betingelser.pdf");
}

foreach($cusm as $mail)
{
 if(($m = trim($mail)) == "" || !ctype_alnum($m{0})) continue;
 if(isset($x)) unset($x);
 $x[] = $m;
 $custom->send($x,'smtp');
 if($m != user_m($usr,$link)) {
  $m = str_replace("<","&lt;",str_replace(">","&gt;",$m));
  $que = "select id,times from used_mails where mail='$m' and user='". $usr ."'";
  $res = mysql_query($que,$link);
  if(mysql_num_rows($res) == 0) {
  	$que = "insert into used_mails set user='". $usr ."', mail='$m',times=1";
	mysql_query($que,$link);
  } else {
  	$r = mysql_fetch_row($res);
	$times = $r[1];
	$times++;
	$que = "update used_mails set times=$times where id=". $r[0];
	mysql_query($que,$link);
  }
 }
}
echo $head;
?>
<res>
 <debug>
<?
$bnr = getUserAccess($usr,$link);
$sql = "insert into K_notat set titel='sup. mail(s) til $tilb',dato=NOW(),k_id='$kid',tilbud_nr=$nr,tilbud_type='X',status='I',bruger=";
$sql .= "$bnr,saelger_id='$usr',tekst='$tilb er blevet mail\'et:\n";
foreach($cusm as $m) {
 $m = str_replace("<","&lt;",str_replace(">","&gt;",$m));
 $sql .= "$m\n";
}
$sql .= "'";
mysql_query($sql,$link);
echo mysql_error($link);
echo "\n" . $sql;
mysql_close($link);
?>
 </debug>
 <success><?= unicode("Så er den blevet mail igen") ?></success>
</res>
