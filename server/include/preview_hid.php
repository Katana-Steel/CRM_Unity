<?php
/**************************************************************************
    This file: ../web/helhed/include/preview_hid.php is part of Helhed Client.

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
	$id = $_GET['hid'];
	$sql = "select * from multi_search where id='$id'";
	$res = mysql_query($sql, $link);
	if(mysql_num_rows($res) > 0) {
		$r = mysql_fetch_assoc($res);
		$save = $r["sql"];
		$sql = "delete from multi_search where id='$id'";
		if(strlen(id) == 3) mysql_query($sql,$link);
		$res = mysql_query($save,$link);
?>
<html>
<head>
<title>Resultat</title>
</head>
<body style="margin:0px;">
<!--
<?php echo $save; ?>
SQL Error: <?php echo mysql_error($link) ?>
-->
<table align="center" cellpadding="5" cellspacing="0" style="border: 0px; padding: 0px; margin: 0px;">
<tr style="">
<?php
		$c = mysql_num_fields($res);
		$align = array();
		for($i=0;$i<$c;$i++) {
		    $type = mysql_field_type($res,$i);
			if($type == "real" || $type == "int")
				$align[$i] = "right";
			else
				$align[$i] = "left";
			$flag = mysql_field_flags($res, $i);
			if(substr_count($flag, "timestamp") > 0)
				$align[$i] = "center";
?>
 <td style="border-bottom: 1px solid black; text-align: center; text-transform: capitalize;">
  <?php echo mysql_field_name($res,$i); ?>
 </td>
<?php
		}
?>
</tr>
<?php
		while($r = mysql_fetch_row($res)) {
?>
<tr>
<?php
			for($i=0;$i<$c;$i++) {
			  $line = true;
			  if( mysql_field_name($res,$i) == 'kid' || mysql_field_name($res,$i) == 'k_id' ) {
			    $k = GetK_OP($r[$i],$link);
			    if( $k["knr"] != "N/A" ) {
                $line = false;
			?>
 <td style="text-align: <?php echo $align[$i]; ?>; padding-left: 15px; padding-right: 15px;" ><?php echo $k["knr"]; ?><br /><?php echo $k["firma"]." ".$k["navn"]; ?></td>
<?php           }
              }
              if($line) { ?>
 <td style="text-align: <?php echo $align[$i]; ?>; padding-left: 15px; padding-right: 15px;" ><?php echo $r[$i]; ?></td>
<?php         }
            }
?>
</tr>
<?php } ?>
</table>
</body>
</html>
<?php
		mysql_close($link);
		exit(0);
	}
?>
