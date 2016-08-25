<?php
/**************************************************************************
    This file: ../web/helhed/app.php is part of Helhed Client.

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
?>
<?php
/* \303\246 = æ, \303\270 = ø, \303\205 = å, \303\251 = é */
$rpath = $_SERVER['SCRIPT_NAME'];
$lpos = strrpos($rpath, '/');
$rpath = substr($rpath, 0,$lpos);

include_once('include/include.php');
align_KTilbud();
srand(time());
setlocale(LC_ALL, 'da_DK');

$head = "<?xml version=\"1.0\"?>\n";
$cid = hexdec((isset($_POST['cid'])) ? $_POST['cid'] : 0 );
$app = true;
$err = "Ingen eller ugyldig 'C. ID'";
if(isset($_POST['cmd'])) {
	switch($_POST['cmd'])
	{
		case 'login':
			$login = false;
			$link = dbcon();
			$okid = false;
			$sql = "select * from Act_Conn where cid =";
			while(!$okid) {
				$cid = rand(16,16*16);
				$res = mysql_query($sql."'$cid'",$link);
				if(mysql_num_rows($res) == 0) $okid = true;
				mysql_free_result($res);
			}
			dologin($link);
			if($login) {
				$sql="select brugernr,tokalvl from Bruger where brugernavn='".$_POST['user']."'";
				$res = mysql_query($sql,$link);
				$r = mysql_fetch_row($res);
				$bgr = $r[0];
				$toka = $r[1];
				mysql_free_result($res);
				mysql_close($link);
				echo $head;
?>
<res>
	<cid><?php echo dechex($cid); ?></cid>
	<usr><?php echo $bgr; ?></usr>
	<toka><?php echo $toka; ?></toka>
	<version>1.0.7</version>
</res>
<?php
			} else {
				$cid = 0;
				$err = "Forkert s\303\246lger eller adgangs kode";
			}
			break;
		case 'logout':
			$err = 'Logout complete';
			$link = dbcon();
			mysql_query("delete from Act_Conn where cid=".$cid,$link);
			mysql_close($link);
			$cid = 0;
			break;
		case 'k_seek':
			$usr = chk_cid($cid);
			if($usr == "") { break; }
			xml_k_seek($usr);
		    break;
		case 'save_temp':
			$usr = chk_cid($cid);
			if($usr == "") { break; }
			xml_save_temp($usr);
			break;
		case 'get_temps':
			$usr = chk_cid($cid);
			if($usr == "") { break; }
			xml_get_temps($usr);
			break;
		case 'seek_gross':
			$usr = chk_cid($cid);
			if($usr == "") { break; }
			xml_gross_seek();
			break;
		case 'stat':
			$usr = chk_cid($cid);
			if($usr == "") { break; }
			xml_statistics($usr);
			break;
		case 'admin':
			$usr = chk_cid($cid);
			if($usr == "") { break; }
			xml_admin($usr);
			break;
		case 'lvo':
			$usr = chk_cid($cid);
			if($usr == "") { break; }
			xml_lvo($usr);
			break;
                case 'rma':
                        $usr = chk_cid($cid);
                        if($usr == "") { break; }
                        xml_rma($usr);
                        break;
		case 'update':
			$link = dbcon();
			$nota = funicode(str_replace("'","\\'",str_replace("\\'","'",$_POST['notat'])));
			$que = "";
			if(isset($_POST['kid'])) {
				$que  = "update ${cust_table} set kundenr='".$_POST['knr']."',firma='".funicode($_POST['navn'])."',navn='";
				$que .= funicode($_POST['att'])."',adresse='".funicode($_POST['adr'])."',post='".funicode($_POST['post']);
				$que .= "',`by`='".funicode($_POST['by'])."',mail='".$_POST['email']."',tlf='".$_POST['tlf']."',fax='";
				$que .= $_POST['fax']."',mobil='".$_POST['mobil']."',bemark='".$nota."',land='".funicode($_POST['land']);
				$que .= "',EAN_SE='".funicode($_POST['eanse'])."' where id=".$_POST['kid'];
			} else {
				$res = mysql_query("select id from ${cust_table} where kundenr='".$_POST['knr']."'",$link);
				if(mysql_num_rows($res) == 0) {
					$que  = "insert ${cust_table} set kundenr='".$_POST['knr']."',firma='".funicode($_POST['navn'])."',navn='";
					$que .= funicode($_POST['att'])."',adresse='".funicode($_POST['adr'])."',post='".funicode($_POST['post']);
					$que .= "',`by`='".funicode($_POST['by'])."',mail='".$_POST['email']."',tlf='".$_POST['tlf']."',fax='";
					$que .= $_POST['fax']."',mobil='".$_POST['mobil']."',bemark='".$nota."',land='".funicode($_POST['land']);
					$que .= "',EAN_SE='".funicode($_POST['eanse'])."',oprette=NOW()";
				}
			}
			if($que != "") mysql_query($que,$link);
			mysql_close($link);
			break;
		case 'create_order':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_create_order($usr,$_POST['file']);
			break;
		case 'create_jour':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_create_jour($usr);
			break;
		case 'update_jour':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_update_jour($usr);
			break;
		case 'kill_order':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_kill_ord($usr);
			break;
		case 'reenable':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_reenable($usr);
			break;
		case 'delivered':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_delivered($usr);
			break;
		case 'get_mail':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_get_mails($usr);
			break;
		case 'get_print':
			$usr = chk_cid($cid);
			if(isset($_POST['sid'])) {
			  xml_stat_list($usr);
			  break;
			};
			$n = $_POST['onr'];
			$sql = "select * from K_notat where tilbud_nr=$n";
			$link = dbcon();
			$res = mysql_query($sql,$link);
			if(mysql_num_rows($res) != 0) {
			  $r = mysql_fetch_assoc($res);
			  if(getUserAccess($usr,$link) < $r['bruger']) {
				$err = "Du har ikke rettigehed til\nat få vist nr: $n";
				$cid = 0;
				break;
			  }
			} else {
				$err = "nr: $n\nblev ikke fundet, tjek om hele nummeret\ner rigtigt intastet.";
				$cid = 0;
				break;
			}
			xml_get_print($n,$link);
			break;
		case 'get_xls':
			$usr = chk_cid($cid);
			$n = $_POST['sql'];
			$link = dbcon();
			xml_get_xls($n,$link);
			break;
		case 'get_curlist':
			$usr = chk_cid($cid);
			$n = $_POST['sql'];
			$k = $_POST['knr'];
			$link = dbcon();
			xml_get_curlist($usr,$n,$k,$link);
			break;
		case 'toka':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_TOKA($_POST['nr']);
			break;
		case 'extra_mails':
			$usr = chk_cid($cid);
			if($usr == "") break;
			xml_extra_mails($usr,$_POST['k_mail'],$_POST['tnr']);
			break;
		default:
			$err = "Denne funktion er endnu ikke\nimplementeret på serveren.";
			$cid = 0;
	}
}
if($cid == 0) {
?>
<?php echo $head; ?>
<res>
	<error><?php echo unicode($err); ?></error>
	<sqlerr><?php echo mysql_error(); ?></sqlerr>
	<post_cid>'<?php if(isset($_POST['cid'])) echo gettype($_POST['cid']); ?>' <?php if(isset($_POST['cid'])) echo $_POST['cid']; ?></post_cid>
	<post_cmd>'<?php echo gettype($_POST['cmd']); ?>' <?php echo $_POST['cmd']; ?></post_cmd>
</res>
<?php
}
?>
