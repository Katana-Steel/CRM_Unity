<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_admin_update.php is part of Helhed Server.

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
	 <a href=\"http://www.keenan.dk/helhed/app/install.htm\" target=\"_blank\">på www.keenan.dk</a><br />
	 eller hvis du sidder i her huset:<br />
	 <a href=\"\\\\192.168.0.125\\ddd1\\helhed\" target=\"_blank\">Ddd1 på Keenan Server</a>
    </td>
   </tr>
   <tr>
    <td width=\"15\">&nbsp;</td>
    <td class=\"note\">
<b>Ændringer/Forbedringer:<b><br />\n".str_replace("\n","<br />\n",funicode($_POST['msg']))."</td>
   </tr>
   <tr>
    <td width=\"15\">&nbsp;</td>
    <td>
     Spørgsmål vdr. denne mail kan henvendes<br />
     til telefon: ".$tlf."
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
 <sql_error><?= $sqlerr ?></sql_error>
 <success><?= unicode("Der er nu givet besked om\nat der er kommet en opdatering.") ?></success>
</res>
