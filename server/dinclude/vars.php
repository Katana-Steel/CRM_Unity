<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/vars.php is part of Helhed Server.

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
$month = array( 1 => "Januar",
				"Februar",
				"Marts",
				"April",
				"Maj",
				"Juni",
				"Juli",
				"August",
				"September", 
				"Oktober",
				"November",
				"December",
				"01" => "Januar",
				"02" => "Februar",
				"03" => "Marts",
				"04" => "April",
				"05" => "Maj",
				"06" => "Juni",
				"07" => "Juli",
				"08" => "August",
				"09" => "September");

$dary = array(	'dag' => date("j",time()),
				'maaned' => date("m",time()),
				'aar' => date("Y",time()) );

?>
