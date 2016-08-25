<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_create_order.php is part of Helhed Client.

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
global $head,$order_path,$rpath;
$link = dbcon();
echo $head;
?>
<res>
<debug><?php
$orderxml = $_SERVER['DOCUMENT_ROOT'].$rpath."/tmp/".$file;
$original = $order_path."/".$file;
rename($original, $orderxml);
$da = new XMLParser($usr,$orderxml,$link);
if(xml_get_error_code($da->parser) != XML_ERROR_NONE) {
 echo xml_error_string(xml_get_error_code($da->parser))." at line: " . xml_get_current_line_number($da->parser) . "\n";
 echo "error in: ".$file;
?>
</debug>
<error><?php echo unicode("Der opstod en fejl kontakt venligst system administratoren"); ?></error>
</res>
<?php
 return;
}
xml_parser_free($da->parser);
if($da->brg == 10) $da->bemark .= "\ntest";
$oid = getOID($da->kid,$da->type,$link);
echo "sql_error(getOID): ". mysql_error() ."\n";
mysql_query("delete from Skurv where id=$oid",$link);
$da->cJourSQL .= "tilbud_nr=$oid,";
$da->cOrdHead .= "tilbud_nr=$oid,";
$da->cLevAddr .= "oid=$oid";
if($da->lev) {
	mysql_query($da->cLevAddr,$link);
}
$s = 0; $b = 0;
foreach($da->gross as $v)
{
 $sql = $da->cOrdHead;
 $sql .= "bemaerk='";
 if($da->klar) $sql .= "<b>Klarg&oslash;res</b><br />";
 $sql .= $da->bemark . "',";
 if($v->type == "S") {
  $sql .= "stk=$v->stk,";
  $s++;
 } else {
  $sql .= "stk=". ($v->stk * -1) .",";
  $b++;
 }
 $sql .= "vare_nr='$v->vid',";
 $sql .= "varetekst='$v->vtxt',";
 $sql .= "pris=$v->pris";
 if($v->rab != "" || $v->rab != NULL) $sql .= ",rabat=$v->rab";
 mysql_query($sql, $link);
 echo "cOrdHead: " . $sql . "\n";
 echo mysql_error($link)."\n\n";
}
$da->cusm[] = $salg = user_m($usr,$link);
defaultMails($da->cusm, $usr, $da->brg, $da->type,$link);
reset($da->cusm);
switch($da->type)
{
case 'T':
$tilb = " Tilbudet";$msub = "Tilbuds nr: $oid";$dc = "tt";$slg = "tilbud";
break;
case 'O':
$tilb = " Ordren";$msub = "Ordre nr: $oid";$dc = "nn";$slg = "ordre";
break;
case 'K':
$tilb = " Konsignationen";$msub = "Konsignations nr: $oid";$dc = "nn";$slg = "konsignation";
break;
case 'A':
$tilb = " Arbejdskortet";$msub = "Arbejdskort nr: $oid";$dc = "tt";$slg = "arbjedskort";
break;
case 'S':
$tilb = " Salgsm&aring;let";$msub = "Salgsmål nr: $oid";$dc = "tt";$slg = "salgsm&aring;l";
break;
}

$da->cJourSQL .= "tekst='de".$dc."e $slg er blevet mailet til:\n";
foreach($da->cusm as $name)
	$da->cJourSQL .= "$name\n";

if($da->klar) $da->cJourSQL .= "<b>Klarg&oslash;res</b>\n";
$da->cJourSQL .= $da->bemark . "'";
mysql_query($da->cJourSQL,$link);
echo mysql_error($link) .  "\njourSQL: ".unicode($da->cJourSQL)."\n";

global $rpath;
echo "rpath: ". $rpath . "\n\n";
reset($da->cusm);
$msg = printm($oid,$da->type,$da->kid,$link);
reset($da->cusm);

$custom = new htmlMimeMail();

$custom->setReturnPath($salg);
$custom->setFrom('"Helhed" <'.$salg.'>');
$custom->setSubject($msub);

$custom->setHtml($msg);

if($type != 'A') {
$custom->addAttachment($custom->getFile($da->type.".pdf"),"Salgs Betingelser.pdf");
}

foreach($da->cusm as $mail)
{
 if(trim($mail) == "") continue;
 $custom->send(array($mail),'mail');
 if($mail != user_m($usr,$link)) {
  $que = "select id,times from used_mails where mail='$mail' and user='". $usr ."'";
  $res = mysql_query($que,$link);
  if(mysql_num_rows($res) == 0) {
  	$que = "insert into used_mails set user='". $usr ."', mail='$mail',times=1";
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
if($da->disSQL != "") mysql_query($da->disSQL,$link);
if($da->period != "") {
    $sql = "insert into calc set tnr=$oid,value='".$da->period."'";
	mysql_query($sql,$link);
}
mysql_query("flush tables",$link);
mysql_close($link);
unlink($orderxml);
reset($da->cusm);
echo " <subpart>\n";
 print_r($da->cusm);
echo "\n </subpart>\n";
?>
</debug>
<success><?php echo unicode("$tilb er nu gemt og mailet til
dem der har bedt om at få det."); ?></success>
</res>
