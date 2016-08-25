<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_stat_totsalg.php is part of Helhed Server.

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
 if(isset($_POST['all'])) $sid = "%"; else $sid = $usr;
 $sql  = "select *,";
 $sql .= "DATE_FORMAT(ndato,'%e') as nd,";
 $sql .= "DATE_FORMAT(ndato,'%c') as nm,";
 $sql .= "DATE_FORMAT(ndato,'%Y') as ny ";
 $sql .= "from K_notat where tilbud_type='O' and saelger_id like '".$sid ."' and tekst not like '%test%'";
 $sql .= " and dato >= '".$_POST['from']."'";
 $sql .= " and dato <= '".$_POST['to']."'";
 $sql .= " order by saelger_id,dato";
 $res = mysql_query($sql,$link);
 $data = Array();
 while( $r = mysql_fetch_assoc($res) ) 
 {
  if($sid != $r["saelger_id"]) $sid = $r["saelger_id"];
  $data[$sid][] = $r["tilbud_nr"];
 }
 $salg = Array();
 $bytte = Array();
echo $head;
?>
<res>
<from><?= $_POST['from'] ?></from>
<to><?= $_POST['to'] ?></to>
<?
foreach( $data as $id => $ary )
 {
  $salg[$id] = 0;
  $bytte[$id] = 0;
?>
<salger>
 <id><?= $id ?></id>
<?
  foreach($ary as $x) 
  {
   $stmp = 0;
   $btmp = 0;
?>
 <order>
  <nr><?= $x ?></nr>
<?
   $sql = "select * from `K-tilbud` where stk>0 and tilbud_nr = $x";
   $res = mysql_query($sql,$link);
   while($r = mysql_fetch_assoc($res)) {
   	$stmp += ($r['stk'] * ((100-$r['rabat'])/100) * $r['pris']);
   }
?>
  <osalg><?= number_format($stmp,2,",",".") ?> kr.</osalg>
<?
   $salg[$id] += $stmp;
   $sql = "select * from `K-tilbud` where stk<0 and tilbud_nr = $x";
   $res = mysql_query($sql,$link);
   while($r = mysql_fetch_assoc($res)) {
   	$btmp += (-1 * $r['stk'] * $r['pris']);
   }
?>
  <obytte><?= number_format($btmp,2,",",".") ?> kr.</obytte>
  <ototal><?= number_format($stmp - $btmp,2,",",".") ?> kr.</ototal>
 </order>
<?
   $bytte[$id] += $btmp;
  }
?>
 <salg><?= number_format($salg[$id],2,",",".") ?> kr.</salg>
 <bytte><?= number_format($bytte[$id],2,",",".") ?> kr.</bytte>
 <total><?= number_format($salg[$id] - $bytte[$id],2,",",".") ?> kr.</total>
</salger>
<?
 }
?>
<? if(count($salg) > 1) { ?>
<salger>
 <id>Totalt</id>
<? 
$totsalg = 0;
foreach($salg as $s)
  $totsalg += $s;
$totbytte = 0;
foreach($bytte as $b)
  $totbytte += $b;
?>
 <salg><?= number_format($totsalg,2,",",".") ?> kr.</salg>
 <bytte><?= number_format($totbytte,2,",",".") ?> kr.</bytte>
 <total><?= number_format($totsalg - $totbytte,2,",",".") ?> kr.</total>
</salger>
<?  } ?>
</res>
