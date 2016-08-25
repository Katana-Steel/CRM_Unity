<?php
/**************************************************************************
    This file: ../web/helhed/include/killordm.php is part of Helhed Client.

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
$file = $_SERVER['DOCUMENT_ROOT'] . $rpath . "/style/style.css";
$st = fopen($file,"r");
$s = fread($st,filesize($file));
fclose($st);
$ret = "<html>
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">
<style>\n${s}\n</style>
<title>$title</title>
</head>
<body>
".order_head("Order nr:",$nr)."

<table>
<tr>
<td>&nbsp;</td>
</tr>
<tr>
<td>
Dette er for godt ordens skyld at fort&aelig;lle de implicerede parter<br />
at <b>Ordre nr: $nr</b> er blevet <b>annulleret</b>.
</td>
</tr>
</table>
</td>

<!-- Left buffer zone -->
<td width=\"45\" bgcolor=\"#999999\">&nbsp;</td>

</tr>
</table>
</body>
</html>";
?>
