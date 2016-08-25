<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/unicode.php is part of Helhed Server.

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
function funicode($str)
{
	$ret = $str;
/*	$ret = str_replace("\303\246","\xE6",$ret);
	$ret = str_replace("\303\270","�",$ret);
	$ret = str_replace("\303\245","�",$ret); 
	$ret = str_replace("\303\206","\xF6",$ret);
	$ret = str_replace("\303\230","�",$ret);
	$ret = str_replace("\303\205","�",$ret);
	$ret = str_replace("\303\251","�",$ret);
	$ret = str_replace("\303\266","�",$ret);
	$ret = str_replace("\303\244","�",$ret);
	$ret = str_replace("\303\226","�",$ret);
	$ret = str_replace("\303\204","�",$ret);  */
	$ret = str_replace("<br>","<br />",$ret);
	$ret = str_replace("'","\\'",str_replace("\\","",$ret));
	return $ret;
}

function to_win1252($ret)
{
	$ret = str_replace("\303\246","�",$ret);
	$ret = str_replace("\303\270","�",$ret);
	$ret = str_replace("\303\245","�",$ret);
	$ret = str_replace("\303\206","�",$ret);
	$ret = str_replace("\303\230","�",$ret);
	$ret = str_replace("\303\205","�",$ret);
	$ret = str_replace("\303\251","�",$ret);
	$ret = str_replace("\303\266","�",$ret);
	$ret = str_replace("\303\244","�",$ret);
	$ret = str_replace("\303\226","�",$ret);
	$ret = str_replace("\303\204","�",$ret); 
	return $ret;
}

function file2unicode($str)
{
	$ret = str_replace("\303\246","�",$str);
	$ret = str_replace("\303\270","�",$ret);
	$ret = str_replace("\303\245","�",$ret);
	$ret = str_replace("\303\206","�",$ret);
	$ret = str_replace("\303\230","�",$ret);
	$ret = str_replace("\303\205","�",$ret);
	$ret = str_replace("\303\251","�",$ret);
	$ret = str_replace("\303\266","�",$ret);
	$ret = str_replace("\303\244","�",$ret);
	$ret = str_replace("\303\226","�",$ret);
	$ret = str_replace("\303\204","�",$ret); 
	$ret = str_replace("<br>","<br />",$ret);
	$ret = str_replace("'","\\'",str_replace("\\","",$ret));
	return $ret;
}

function unicode($str)
{
	$ret = $str;
	$ret = str_replace("�","\303\246",$ret);
	$ret = str_replace("�","\303\270",$ret);
	$ret = str_replace("�","\303\245",$ret);
	$ret = str_replace("�","\303\206",$ret);
	$ret = str_replace("�","\303\230",$ret);
	$ret = str_replace("�","\303\205",$ret);
	$ret = str_replace("�","\303\251",$ret);
	$ret = str_replace("�","\303\266",$ret);
	$ret = str_replace("�","\303\244",$ret);
	$ret = str_replace("�","\303\226",$ret);
	$ret = str_replace("�","\303\204",$ret);
	$ret = str_replace("\303\203\302\246","\303\246",$ret);
	$ret = str_replace("\303\203\302\270","\303\270",$ret);
	$ret = str_replace("\303\203\302\245","\303\245",$ret); 
/*	$ret = str_replace("\303\203\302\206","\303\206",$ret);
	$ret = str_replace("\303\203\302\230","\303\230",$ret);
	$ret = str_replace("\303\203\302\205","\303\205",$ret); */ 
	$ret = str_replace("&","&amp;",$ret);
	$ret = str_replace("<br>","<br />",$ret);
	return $ret;
}

?>
