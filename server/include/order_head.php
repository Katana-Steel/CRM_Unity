<?php
/**************************************************************************
    This file: ../web/helhed/include/order_head.php is part of Helhed Client.

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

    Copyright 2008, 2011 René Kjellerup aka Katana Steel
**************************************************************************/
?>
<?php
switch($type) {
case "T":
	$str = "Tilbuds nr:";
	break;
case "O":
	$str = "Ordre nr:";
	break;
case "K":
	$str = "Konsignations nr:";
	break;
case "A":
	$str = "Arbejdskort nr:";
	break;
case "S":
	$str = "Salgsm&aring;l ${machine} nr:";
	break;
}
$request_uri = $_SERVER['REQUEST_URI'];
$scriptname = $_SERVER['SCRIPT_NAME'];
include ("theme/${theme_name}/head.tpl");
?>
