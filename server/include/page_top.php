<?php
/**************************************************************************
    This file: ../web/helhed/include/page_top.php is part of Helhed Client.

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

    Copyright 2008, 2009, 2010 René Kjellerup aka Katana Steel
**************************************************************************/

$ret = "
<table align=\"center\" border=\"0\">
<tr>
<!-- Left buffer zone -->
<td width=\"15\">&nbsp;</td>

<!-- Where the page is -->
<td style=\"border: solid black 1px;\">
<script language=\"JavaScript\" type=\"text/javascript\">
function bugs()
{
open(\"bugs.php?page=". $_SERVER['REQUEST_URI'] ."\",\"_blank\",\"HEIGHT=350,WIDTH=300\");
}
</script>
";
include ("theme/${theme}/top.tpl");
$ret .= "
 <table align=\"center\" style=\"font-family: Arial;\">
  <tr>
   <td rowspan=\"4\" align=\"left\">
    <img border=\"0\" height=\"115\" src=\"images/logo.png\" alt=\"\" />
   </td>
   <td style=\"font-size: 26pt; font-weight: bold;\">
    ${str}
   </td>
   <td align=\"right\" width=\"85\" style=\"font-size: 16pt; font-style: italic;\">
    ${id}<br />
   </td>
  </tr>
  <tr>
   <td style=\"font-size: 16pt; font-style: italic; font-weight: bold;\">
    &nbsp;
   </td>
   <td align=\"right\" style=\"font-size: 10pt; font-weight: bold;\">
    &nbsp;
   </td>
  </tr>
  <tr>
   <td style=\"font-size: 10pt; font-style: italic; font-weight: bold;\">
    &nbsp;
   </td>
   <td>&nbsp;</td>
  </tr>
  <tr>
   <td style=\"font-size: 10pt; font-style: italic; font-weight: bold;\">
    &nbsp;
   </td>
   <td>&nbsp;</td>
  </tr>
  <tr>
   <td>
   </td>
  </tr>
 </table>
";
?>
