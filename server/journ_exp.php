#!/usr/bin/php
<?php
/**************************************************************************
    This file: /var/www/html/helhed/journ_exp.php is part of Helhed Server.

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

    Copyright 2012 RenÃ© Kjellerup aka Katana Steel
**************************************************************************/
?>
<?php
$pwd = "/var/www/html/helhed/";
chdir($pwd);

include_once('html_mime_mail_2.5/htmlMimeMail.php');
include_once('include/UserControl.php');
include_once('include/startdb.htm');

function generate_mail($clients)
{
global $pwd;
$mtxt = "
<html>
<head>
<title>HELHED - Journals overdue for follow up</title>
";

$file = $pwd . "/style/style.css";
$s = file_get_contents($file);
$mtxt .= "
<style>\n$s\na { color: black; };</style>

</head>
<body>
<!-- list length " . count($clients) . " -->
<table align='center'>
<tr>
<td colspan='2'>Your overdue clients</td>
</tr>
<tr>
<td>Client Number</td><td>Client Name</td>
";
foreach($clients as $c) {
   $mtxt .= "
<tr>
<td>${c['cnr']}</td>
<td>${c['cname']}</td>
</tr>
";
if($c['nid'] != '') {
  $link = dbcon();
  mysql_query("update K_notat set status='A' where notat_id=${c['nid']}",$link);
  mysql_close($link);
}
}
$mtxt .= "
</table>
</body>
";
return $mtxt;
}

function helhed_mail_output($usr, $msg)
{

$custom = new htmlMimeMail();
$custom->setReturnPath('helhed.mailer@bhsribe.dk');

$custom->setFrom('"Brdr. Holst Sørensen A/S" <helhed.mailer@bhsribe.dk>');
$custom->setSubject("HELHED - Journals overdue for follow up");

$custom->setTextEncoding('8bit');
$custom->setTextCharset('utf-8');
$custom->setHtmlCharset('utf-8');
$custom->setHeadCharset('utf-8');

$custom->setHtml($msg);
$custom->send(array($usr),'smtp');
}

$link = dbcon();
$res = mysql_query("select k_id,saelger_id,notat_id from `K_notat` where status='I' and IFNULL(tilbud_type,'J')='J' and ndato <= NOW() order by saelger_id", $link);
$mm = '';
$c = array();
$dbg = array();
$dbg[] = array('cnr' => 'below should be the sales persons email','cname' => 'Here ourght to be the number of mails we send to him','nid' => '');
while($r = mysql_fetch_assoc($res))
{
  $um = user_m($r['saelger_id'], $link);
  if($mm != $um) {
    if($mm != '') {
        helhed_mail_output($mm, generate_mail($c));
        $dbg[] = array('cnr' => $mm, 'cname' => count($c),'nid' => '');
    }
    $mm = $um;
    $c = array();
  }
  $mss = mysql_fetch_assoc(mysql_query("select * from keenan_kunde where id=".$r['k_id'],$link));
  $c[] = array('cnr' => $mss['kundenr'], 'cname' => $mss['firma'] . " " . $mss['navn'], 'nid' => $r['notat_id']);
}

if(count($c)>0) {
  helhed_mail_output($mm, generate_mail($c));
  $dbg[] = array('cnr' => $mm, 'cname' => count($c), 'nid' => '');
}

helhed_mail_output("rk.katana.steel@gmail.com", generate_mail($dbg));

mysql_close($link);

?>
