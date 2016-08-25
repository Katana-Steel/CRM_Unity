<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_k_seek.php is part of Helhed Client.

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
	global $head, $cust_table;
	$link = dbcon();
	$bgr = getUserAccess($usr, $link);

    $kid = 0;
    $sql = "";
    if(isset($_POST['kid'])) {
        $sql = "select * from ${cust_table} where `id`=".$_POST['kid'];
    }
    if(isset($_POST['knr']) && $sql == "") {
        $sql = "select * from ${cust_table} where kundenr like '".funicode($_POST['knr'])."%'";
    }
    if(isset($_POST['knavn']) && $sql == "") {
        $sql = "select * from ${cust_table} where firma like '%".funicode($_POST['knavn'])."%'";
    }
    if(isset($_POST['katt']) && $sql == "") {
        $sql = "select * from ${cust_table} where navn like '%".funicode($_POST['katt'])."%'";
    }
    if(isset($_POST['kadr']) && $sql == "") {
        $sql = "select * from ${cust_table} where adresse like '%".funicode($_POST['kadr'])."%'";
    }
    if(isset($_POST['kpost']) && $sql == "") {
        $sql = "select * from ${cust_table} where post like '".funicode($_POST['kpost'])."%'";
    }
    if(isset($_POST['kby']) && $sql == "") {
        $sql = "select * from ${cust_table} where `by` like '".funicode($_POST['kby'])."%'";
    }
    if($sql != "") {
        $res = mysql_query($sql,$link);
        $num = mysql_num_rows($res);
        switch($num)
        {
        case 0:
            echo $head;
?>
<res>
	<error>Der er ingen kunde med
kundenr/id: <?php
if(isset($_POST['knr'])) {
echo $_POST['knr'];
} else if(isset($_POST['kid'])) {
echo $_POST['kid'];
}
?> oprettet</error>
    <sql><?php echo $sql; ?></sql>
</res>
<?php
            break;
        case 1:
            $kd = mysql_fetch_assoc($res);
            $kid = $kd['id'];
            $res2 = mysql_query("select * from K_notat where k_id=".$kid." and bruger <= ".$bgr." order by dato desc,tilbud_nr desc",$link);
?>
<?php echo $head ?>
<res>
  <cus>
	<kid><?php echo $kd['id']; ?></kid>
	<kdato><?php echo date("d/m/Y", strtotime($kd['oprette'])); ?></kdato>
	<knr><?php echo $kd['kundenr']; ?></knr>
	<navn><?php echo unicode($kd['firma']); ?></navn>
	<att><?php echo unicode($kd['navn']); ?></att>
	<adr><?php echo unicode($kd['adresse']); ?></adr>
	<post><?php echo unicode($kd['post']); ?></post>
	<by><?php echo unicode($kd['by']); ?></by>
	<land><?php echo unicode($kd['land']); ?></land>
	<ean_se><?php echo unicode($kd['EAN_SE']); ?></ean_se>
<?php
$mail = split(";",$kd['mail']);
foreach($mail as $x) {
?>
	<email><?php echo $x; ?></email>
<?php } ?>
	<tlf><?php echo $kd['tlf']; ?></tlf>
	<fax><?php echo $kd['fax']; ?></fax>
	<mobil><?php echo $kd['mobil']; ?></mobil>
	<nota><?php echo unicode($kd['bemark']); ?></nota>
  </cus>
<?php
            while($jd = mysql_fetch_assoc($res2)) {
?>
  <jour>
	<notat><?php echo $jd['notat_id']; ?></notat>
	<sid><?php echo $jd['saelger_id']; ?></sid>
	<dato><?php echo date("d/m/Y", strtotime($jd['dato'])); ?></dato>
	<nota_text><?php echo unicode(str_replace("\n","<br>",$jd['tekst'])); ?></nota_text>
	<luk><?php echo unicode($jd['lukke_pro']); ?></luk>
	<status><?php echo $jd['status']; ?></status>
	<lev><?php echo $jd['lev']; ?></lev>
<?php
                $tilb = unicode($jd['tilbud_nr']);
                switch($jd['tilbud_type']) {
                case 'T':
?>
	<til><?php echo $tilb; ?></til>
<?php
                    break;
                case 'O':
?>
	<ord><?php echo $tilb; ?></ord>
<?php
                    break;
                case 'K':
?>
	<kon><?php echo $tilb; ?></kon>
<?php
                    break;
                case 'A':
?>
	<arb><?php echo $tilb; ?></arb>
<?php
                    break;
                case 'S':
?>
	<slg><?php echo $tilb; ?></slg>
<?php
                    break;
                case 'X':
                    $pos = strpos($jd['titel'],'mail');
                    if($pos === false) {
?>
	<del><?php echo $tilb; ?></del>
<?php
                    } else {
?>
	<mail><?php echo $tilb; ?></mail>
<?php
                    }
                    break;
                default:
?>
	<titel><?php echo unicode($jd['titel']); ?></titel>
<?php
                    break;
                }
?>
  </jour>
<?php
            }
?>
</res>
<?php
            mysql_free_result($res2);
            break;
        default:
            echo $head;
?>
<res>
	<ant><?php echo $num; ?></ant>
<?php
            while($r = mysql_fetch_assoc($res)) {
?>
	<cus>
		<kid><?php echo $r['id']; ?></kid>
		<knr><?php echo $r['kundenr']; ?></knr>
		<navn><?php echo unicode($r['firma']); ?> <?php echo unicode($r['navn']); ?></navn>
		<post><?php echo unicode($r['post']); ?></post>
		<by><?php echo unicode($r['by']); ?></by>
	</cus>
<?php
            }
?>
</res>
<?php
            break;
        }
        mysql_free_result($res);
    }
    mysql_close($link);
?>
