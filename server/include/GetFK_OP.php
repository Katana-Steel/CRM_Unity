<?php
/**************************************************************************
    This file: ../web/helhed/include/GetFK_OP.php is part of Helhed Client.

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

	$que = "select kundenr,firma,navn,adresse,post,`by`,tlf,mobil,fax,mail from kunde where id = ".$k_id;
	$res = mysql_query($que,$link);
	if(mysql_num_rows($res) == 0) {
		$tmp = array( "knr" => "N/A", "firma" => "N/A", "navn" => "N/A", "addr" => "N/A", "post" => "N/A",
		              "by" => "N/A", "tlf" => "N/A", "mobil" => "N/A", "fax" => "N/A", "mail" => "N/A");
	} else {
		$row = mysql_fetch_row($res);
		$tmp = array( "knr" => $row[0], "firma" => $row[1], "navn" => $row[2], "adr" => $row[3], "post" => $row[4],
		              "by" => $row[5], "tlf" => $row[6], "mobil" => $row[7], "fax" => $row[8], "mail" => $row[9]);
	}
?>
