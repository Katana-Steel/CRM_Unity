<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_admin_update.php is part of Helhed Client.

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
$sql = "select mail,brugernavn,tlf from Bruger";
$res = mysql_query($sql,$link);
$sqlerr = mysql_error($link);
$mails = array();
$salg = "";
$tlf = "";
while($r = mysql_fetch_row($res))
{
	if($r[1] != $usr)
		$mails[] = $r[0];
	else {
		$salg = $r[0];
		$tlf = $r[2];
	}
}

$app_path = str_replace($_SERVER['DOCUMENT_ROOT'],"",$_SERVER['SCRIPT_FILENAME']);
$app_path = str_replace("index.php", "app/indtall.htm", $app_path);

$mails = array_unique($mails);
$email = new htmlMimeMail();

$email->setReturnPath($salg);
$email->setFrom('"Helheds Modulet Administrator" <'.$salg.'>');
$email->setSubject("Opdatering til Helheds modulet");
$msg = "<html>
 <head>
  <title>Opdatering til Helheds modulet</title>
 </head>
 <style>
 	.hdr {
	  font-size:18pt;
	  font-weight: bold;
	  text-decoration: underline;
	  text-align: center;
	  padding-bottom: 25px;
	}
	.note {
	  font-family: monospace;
	  font-size: 10pt;
	  border: 1px solid black;
	}
 </style>
 <body>
  <table>
   <tr>
    <td colspan=\"2\" class=\"hdr\">Opdatering til Helheds modulet</td>
   </tr>
   <tr>
    <td width=\"15\">&nbsp;</td>
    <td>
     Der er nu blevet frigivet en opdatering til Helheds modulet<br />
     og den kan hentes her:<br />
     <a href=\"http://". $_SERVER['SERVER_NAME'] . $app_path ."\" target=\"_blank\">p&aring; ". $_SERVER['SERVER_NAME'] ."</a><br />
     eller kontakt Helhed's Administrator for at f&aring; en addresse hvor p&aring; opdateringen kan hæntes.<br />
    </td>
   </tr>
   <tr>
    <td width=\"15\">&nbsp;</td>
    <td class=\"note\">
<b>&Aelig;ndringer/Forbedringer:<b><br />\n".str_replace("\n","<br />\n",funicode($_POST['msg']))."</td>
   </tr>
   <tr>
    <td width=\"15\">&nbsp;</td>
    <td>
     Sp&oslash;rgsm&aring;l vdr. denne mail kan henvendes<br />
     til telefon: '".$tlf."' eller ved at besvare denne mail.
    </td>
   </tr>
  </table>
 </body>
</html>
";
$email->setHtml($msg);

$email->send($mails,'smtp');
?>
<res>
 <sql_error><?php echo $sqlerr; ?></sql_error>
 <success><?php echo unicode("Der er nu givet besked om\nat der er kommet en opdatering."); ?></success>
</res>
