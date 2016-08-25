<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_k_seek.php is part of Helhed Server.

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
	global $head;
	$link = dbcon();
	$bgr = getUserAccess($usr, $link);
	
			$kid = 0;
			$sql = "";
			if(isset($_POST['knr'])) {
				$sql = "select * from keenan_kunde where kundenr like '".funicode($_POST['knr'])."%'";
			} 
			if(isset($_POST['knavn']) && $sql == "") {
				$sql = "select * from keenan_kunde where firma like '%".funicode($_POST['knavn'])."%'";
			}
			if(isset($_POST['katt']) && $sql == "") {
				$sql = "select * from keenan_kunde where navn like '%".funicode($_POST['katt'])."%'";
			}
			if(isset($_POST['kadr']) && $sql == "") {
				$sql = "select * from keenan_kunde where adresse like '%".funicode($_POST['kadr'])."%'";
			}
			if(isset($_POST['kpost']) && $sql == "") {
				$sql = "select * from keenan_kunde where post like '".funicode($_POST['kpost'])."%'";
			}
			if(isset($_POST['kby']) && $sql == "") {
				$sql = "select * from keenan_kunde where `by` like '".funicode($_POST['kby'])."%'";
			}
			if($sql != "") {
				$res = mysql_query($sql,$link);
				$num = mysql_num_rows($res);
				if($num == 1) {
					$r = mysql_fetch_assoc($res);
					$kid = $r['id'];
				}
				if($num > 1) {
?>
<?= $head ?>
<res>
	<ant><?= $num ?></ant>
<?					while($r = mysql_fetch_assoc($res)) { ?>
	<cus>
		<kid><?= $r['id'] ?></kid>
		<knr><?= $r['kundenr'] ?></knr>
		<navn><?= to_win1252($r['firma']) ?> <?= to_win1252($r['navn']) ?></navn>
		<post><?= unicode($r['post']) ?></post>
		<by><?= unicode($r['by']) ?></by>
	</cus>
<? 					} ?>
</res>
<?					
				}
			}
			if(($kid = (isset($_POST['kid'])) ? $_POST['kid'] : $kid ) != 0) { 
				$res = mysql_query("select * from keenan_kunde where id=".$kid,$link);
				$kd = mysql_fetch_assoc($res);
				$res2 = mysql_query("select * from K_notat where k_id=".$kid." and bruger <= ".$bgr." order by dato desc,tilbud_nr desc",$link);
?>
<?= $head ?>
<res>
  <cus>
	<kid><?= $kd['id'] ?></kid>
	<kdato><?= date("d/m/Y", strtotime($kd['oprette'])) ?></kdato>
	<knr><?= $kd['kundenr'] ?></knr>
	<navn><?= to_win1252(unicode($kd['firma'])) ?></navn>
	<att><?= to_win1252(unicode($kd['navn'])) ?></att>
	<adr><?= to_win1252(unicode($kd['adresse'])) ?></adr>
	<post><?= unicode($kd['post']) ?></post>
	<by><?= to_win1252(unicode($kd['by'])) ?></by>
	<land><?= unicode($kd['land']) ?></land>
	<ean_se><?= unicode($kd['EAN_SE']) ?></ean_se>
<?
$mail = split(";",$kd['mail']);
foreach($mail as $x) {
?>
	<email><?= $x ?></email>
<? } ?>
	<tlf><?= $kd['tlf'] ?></tlf>
	<fax><?= $kd['fax'] ?></fax>
	<mobil><?= $kd['mobil'] ?></mobil>
	<nota><?= unicode($kd['bemark']) ?></nota>
  </cus>
<?
				while($jd = mysql_fetch_assoc($res2)) {
?>
  <jour>
	<notat><?= $jd['notat_id'] ?></notat>
	<sid><?= $jd['saelger_id'] ?></sid>
	<dato><?= date("d/m/Y", strtotime($jd['dato'])) ?></dato>
	<nota_text><?= unicode(str_replace("\n","<br>",$jd['tekst'])) ?></nota_text>
	<luk><?= unicode($jd['lukke_pro']) ?></luk>
	<status><?= $jd['status'] ?></status>
	<lev><?= $jd['lev'] ?></lev>
<?
					$tilb = unicode($jd['tilbud_nr']);
					switch($jd['tilbud_type']) {
					case 'T':
?>
	<til><?= $tilb ?></til>
<?							
						break;
					case 'O':
?>
	<ord><?= $tilb ?></ord>
<?							
						break;
					case 'K':
?>
	<kon><?= $tilb ?></kon>
<?							
						break;
					case 'A':
?>
	<arb><?= $tilb ?></arb>
<?							
						break;
					case 'S':
?>
	<slg><?= $tilb ?></slg>
<?							
						break;
					case 'X':
						$pos = strpos($jd['titel'],'mail');
						if($pos === false) {
?>
	<del><?= $tilb ?></del>
<?							
						} else {
?>
	<mail><?= $tilb ?></mail>
<?							
						}
						break;
					default:
?>
	<titel><?= unicode($jd['titel']) ?></titel>
<?							
						break;
					}
?>
  </jour>
<?
				}
?>
</res>
<?
				mysql_free_result($res);
				mysql_free_result($res2);
			} else {
				echo $head;
?>
<res>
	<error>Der er ingen kunde med 
kundenr: <?= $_POST['knr'] ?> oprettet</error>
</res>
<?
			}
		mysql_close($link);
?>
