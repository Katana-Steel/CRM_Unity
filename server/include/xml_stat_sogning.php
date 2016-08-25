<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_stat_sogning.php is part of Helhed Client.

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
 global $head;
 $txt = isset($_POST['Txt']);
 $t = isset($_POST['T']);
 $o = isset($_POST['O']);
 $k = isset($_POST['K']);
 $a = isset($_POST['A']);
 $to = $_POST['to'];
 $from = $_POST['from'];
 $str = str_replace("'","",str_replace("\\","",funicode($_POST['str'])));
 if($t && $o && $k && $a) {
   $type = "type != 'X'";
 } else {
   $type = "";
   if($t)          $type .= "type = 'T'";
   if($type != "" && ($o || $k || $a)) $type .= " or ";
   if($o)          $type .= "type = 'O'";
   if($type != "" && ($k || $a) && $o) $type .= " or ";
   if($k)          $type .= "type = 'K'";
   if($type != "" && $a && $k) $type .= " or ";
   if($a)          $type .= "type = 'A'";
 }
 $ktil = "select * from `K-tilbud` where ( $type ) and ( ";
 if(isset($_POST['Txt'])) {
   $ktil .= "bemaerk like '%$str%' or lev_kunde like '%$str%' or vare_nr like '%$str%' or varetekst like '%$str%' or reknr like '%$str%'";
 } else {
   $ktil .= "vare_nr like '%$str%' or varetekst like '%$str%' or reknr like '%$str%'";
 }
 $ktil .= " ) and ( dato <= '$to' and dato >= '$from' ) ";
 if(isset($_POST['order'])) {
  if($_POST['order'] != 3) {
    $ktil .= "group by tilbud_nr";
  }
  switch($_POST['order']) {
  case 3:
  case 1:
   $ktil .= " order by kunde_nr,dato";
   break;
  case 2:
   $ktil .= " order by dato,kunde_nr";
   break;
  }
 }
 $ary = array();
 $res = mysql_query($ktil,$link);
 $save = $ktil;
 $nrows = mysql_num_rows($res);
 $mysqlerr = mysql_error($link) . "\n\nsql: " .$ktil."\n";
 while ( $r = mysql_fetch_assoc($res)) {
   $ary[] = $r;
 }
 mysql_free_result($res);
 $kinfo = array();
 foreach( $ary as $row ) {
   $knr = $row["kunde_nr"];
   if(!is_array($kinfo[$knr])) {
     $sql = "select * from kunde where `id` = $knr or kundenr = '$knr'";
     $res = mysql_query($sql,$link);
     $r = mysql_fetch_assoc($res);
	 $kinfo[$knr] = $r;
	 mysql_free_result($res);
   }
 }
?>
<?php echo $head; ?>
<res>
 <sqlstr><?php echo str_replace(">","&gt;",str_replace("<","&lt;",str_replace("'","\\'",unicode($save)))); ?></sqlstr>
 <order><?php echo $_POST["order"]; ?></order>
<?php
switch($_POST['order'])
{
case 3:
case 1:
 $d = 0;
 foreach( $ary as $r ) {
  if($d != $r["kunde_nr"]) {
   $knr = $r["kunde_nr"];
   if($d != 0) {
?>
 </kdat>
<?php } ?>
 <kdat>
  <knr><?php echo unicode($kinfo[$knr]["kundenr"]); ?></knr>
  <kfirma><?php echo unicode($kinfo[$knr]["firma"]); ?></kfirma>
  <katt><?php echo unicode($kinfo[$knr]["navn"]); ?></katt>
  <kadr><?php echo unicode($kinfo[$knr]["adresse"]); ?></kadr>
  <kpost><?php echo unicode($kinfo[$knr]["post"]); ?></kpost>
  <kby><?php echo unicode($kinfo[$knr]["by"]); ?></kby>
<?php
   $d = $knr;
  }
?>
  <type>
   <nr><?php echo $r["tilbud_nr"]; ?></nr>
   <dato><?php echo $r["dato"]; ?></dato>
   <stk><?php echo $r["stk"]; ?></stk>
   <vnr><?php echo unicode($r["vare_nr"]); ?></vnr>
   <vtxt><?php echo unicode($r["varetekst"]); ?></vtxt>
<?php
    $sql = "select lev from K_notat where dato='".$r["dato"]. "' and tilbud_nr='".$r["tilbud_nr"]."'";
	$res = mysql_query($sql);
	$fkn = mysql_fetch_row($res);
?>
    <lev><?php echo ($fkn[0] == "A") ? unicode("Leveret") : unicode("");; ?></lev>
<?php  mysql_free_result($res); ?>
  </type>
<?php
 }
 if($d != 0) {
?>
 </kdat>
<?php }
 break;
case 2:
 $d = 0;
 foreach( $ary as $r ) {
  if($d != $r["dato"]) {
   if($d != 0) {
?>
 </kdat>
<?php } ?>
 <kdat>
  <dato><?php echo $r["dato"]; ?></dato>
<?php
   $d = $knr;
  }
  $knr = $r["kunde_nr"];
?>
  <type>
   <knr><?php echo unicode($kinfo[$knr]["kundenr"]); ?></knr>
   <kfirma><?php echo unicode($kinfo[$knr]["firma"]); ?></kfirma>
   <katt><?php echo unicode($kinfo[$knr]["navn"]); ?></katt>
   <kadr><?php echo unicode($kinfo[$knr]["adresse"]); ?></kadr>
   <kpost><?php echo unicode($kinfo[$knr]["post"]); ?></kpost>
   <kby><?php echo unicode($kinfo[$knr]["by"]); ?></kby>
   <nr><?php echo $r["tilbud_nr"]; ?></nr>
  </type>
<?php
 }
 if($d != 0) {
?>
 </kdat>
<?php }
 break;
}
?>
 <num_row><?php echo $nrows; ?></num_row>
<?php if($nrows == "") { ?>
 <mysql_err><?php echo str_replace("<","&lt;",str_replace(">","&gt;",$mysqlerr)); ?></mysql_err>
<?php } ?>
 <str><?php echo $str; ?></str>
 <derror>Multi Search will be supported soon</derror>
</res>
