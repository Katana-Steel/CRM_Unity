<?php
/**************************************************************************
    This file: ../web/helhed/include/preview_sid.php is part of Helhed Client.

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
  setlocale(LC_ALL,'da');
  $cid = $_GET['sid'];
  $sql = "select * from stat_list where uid='$cid'";
  $res = mysql_query($sql,$link);
  if(mysql_num_rows($res)!= 0)
  {
  	$r = mysql_fetch_assoc($res);
    $sid = $r["sid"];
    $to = $r["to"];
    $from = $r["from"];
    $sql = "delete from stat_list where uid='$cid'";
    mysql_query($sql,$link);
	$user = user($sid,$link);
	$idx = strpos($user,"&nbsp;");
	$user = substr($user,0,$idx);
	$tnr = array();
	$sql = "select tilbud_nr from K_notat where dato <= '$to' and dato >= '$from' and saelger_id='$sid' and tilbud_type='O' group by tilbud_nr asc";
	$res = mysql_query($sql,$link);
	while($r = mysql_fetch_row($res))
		$tnr[] = $r[0];

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Forevisning</title>
</head>
<body>
<table align="center" style="margin: 0px; border-bottom: 2px solid black" width="450">
<tr>
<td colspan="4">Provitions liste for: <b><?php echo $user; ?></b></td>
</tr>
<tr>
<td colspan="4">I tids perioden: <?php
    $time = strtotime($from);
	echo strftime("%e. %b %Y ",$time) ." - ";
    $time = strtotime($to);
	echo strftime("%e. %b %Y ",$time);
?></td>
</tr>
<tr>
<td colspan="4">&nbsp;</td>
</tr>
<tr>
<td>Ordre nr:</td><td align="center">Salg</td><td align="center">Bytte</td><td align="center">I Alt</td>
</tr>
<tr>
<td colspan="4" style="border-top: 1px solid black;">&nbsp;</td>
</tr>
<?php
    $ts=0;
    $tb=0;
	foreach($tnr as $t) {
?>
<tr>
 <td><?php echo $t; ?></td>
<?php
		$sql = "select * from `K-tilbud` where tilbud_nr='$t'";
		$res = mysql_query($sql,$link);
		$tmps = 0;
		$tmpb = 0;
		while($r = mysql_fetch_assoc($res)) {
			$sa = 0;
			$by = 0;
			if($r["stk"] > 0) {
			  $rabat = 1.0 - ($r["rabat"] / 100.0);
			  $sa = $r["stk"] * ($r["pris"] * $rabat);
			} else {
			  $by = (-1 * $r["stk"]) * $r["pris"];
			}
			$tmps += $sa;
			$tmpb += $by;
		}
		mysql_free_result($res);
?>
 <td align="right">kr. <?php echo number_format($tmps,2,',','.'); ?></td>
 <td align="right">kr. <?php echo number_format($tmpb,2,',','.'); ?></td>
 <td align="right">kr. <?php echo number_format($tmps-$tmpb,2,',','.'); ?></td>
</tr>
<?php
		$ts += $tmps;
		$tb += $tmpb;
	}
?>
<tr style="border-top: 2px solid black;">
 <td>Totalt: </td>
 <td align="right">kr. <?php echo number_format($ts,2,',','.'); ?></td>
 <td align="right">kr. <?php echo number_format($tb,2,',','.'); ?></td>
 <td align="right">kr. <?php echo number_format($ts-$tb,2,',','.'); ?></td>
</tr>
</table>
</body>
</html>
<?php
	mysql_close($link);
	exit(0);
  }
?>
