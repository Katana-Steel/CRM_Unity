<?php
/**************************************************************************
    This file: ../web/helhed/kunder_csv.php is part of Helhed Client.

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
$rmaddr = $_SERVER['REMOTE_ADDR'];
if((strncmp($rmaddr,"192.168.0",9) == 0) || ($rmaddr == "80.160.156.42")){
    include('include/include.php');
	header( "Content-type: plain/text");
	header( "Content-Disposition: atachment; filename=kunde_liste.csv");
	$link = dbcon();
	$res = mysql_query("select id,kundenr,firma,navn,adresse,post,`by` from kunde where (land like 'dk' or land like 'danmark') and post > 0 order by post",$link);
	$f = mysql_num_fields($res);
	while($r=mysql_fetch_row($res)) {
		for($i=0;$i<$f;$i++) {
			// echo "\"";
			echo funicode($r[$i]);
			if($i == 2) echo " " . funicode($r[++$i]);
			// echo "\"";
			echo ";";
		}
		echo "DK\r\n";
	}
	mysql_free_result($res);
	mysql_close($link);
} else {
	header("HTTP/1.1 403 Forbidden");
}
?>
