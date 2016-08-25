<?php
/**************************************************************************
    This file: ../web/helhed/include/preview_xls.php is part of Helhed Client.

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
function xlsBOF() {
    echo pack("ssssss", 0x809, 0x8, 0x0, 0x10, 0x0, 0x0);
    return;
}
// Excel end of file footer
function xlsEOF() {
    echo pack("ss", 0x0A, 0x00);
    return;
}
// Function to write a Number (double) into Row, Col
function xlsWriteNumber($Row, $Col, $Value) {
    echo pack("sssss", 0x203, 14, $Row, $Col, 0x0);
    echo pack("d", $Value);
    return;
}
// Function to write a label (text) into Row, Col
function xlsWriteLabel($Row, $Col, $Value ) {
    $L = strlen($Value);
    echo pack("ssssss", 0x204, 8 + $L, $Row, $Col, 0x0, $L);
    echo $Value;
	return;
}

$xid = $_GET['xls'];
$sql = "select * from multi_search where id='$xid'";
$res = mysql_query($sql,$link);
 if(mysql_num_rows($res)!= 0)
 {
	$r = mysql_fetch_assoc($res);
	header( "Content-type: application/x-unknown");
	header( "Content-Disposition: atachment; filename=liste.xls");
	$save = str_replace("\\","",$r["sql"]);
	mysql_free_result($res);
	$sql = "delete from multi_search where id='$xid'";
	mysql_query($sql,$link);
	$res = mysql_query($save,$link);
	$ary = array();
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
	xlsBOF();
	xlsWriteLabel(0,0,"Kunde nr.");
	xlsWriteLabel(0,1,"Tlf");
	xlsWriteLabel(0,2,"Firma");
	xlsWriteLabel(0,3,"Att");
	xlsWriteLabel(0,4,"Adresse");
	xlsWriteLabel(0,5,"Post nr.");
	xlsWriteLabel(0,6,"By");
	xlsWriteLabel(0,8,"Email");
/*	xlsWriteLabel(0,10,"no. found "+count($kinfo));
	xlsWriteLabel(1,9,"sql:");
	xlsWriteLabel(1,10,$save); */
	$nr = 1;
	foreach($kinfo as $knd) {
		xlsWriteLabel($nr,0,$knd["kundenr"]);
		xlsWriteLabel($nr,1,$knd["tlf"]);
		xlsWriteLabel($nr,2,$knd["firma"]);
		xlsWriteLabel($nr,3,$knd["navn"]);
		xlsWriteLabel($nr,4,$knd["adresse"]);
		xlsWriteLabel($nr,5,$knd["post"]);
		xlsWriteLabel($nr,6,$knd["by"]);
		xlsWriteLabel($nr,8,$knd["email"]);
		$nr++;
	}
	xlsEOF();
	mysql_close($link);
	exit(0);
 }
?>
