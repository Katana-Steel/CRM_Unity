<?php
/**************************************************************************
    This file: ../web/helhed/unicode.php is part of Helhed Client.

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

function funicode($str)
{
    $ret = $str; /*
	$ret = str_replace("\303\246","\346",$ret);
	$ret = str_replace("\303\270","\270",$ret);
	$ret = str_replace("\303\245","\345",$ret);
	$ret = str_replace("\303\206","\306",$ret);
	$ret = str_replace("\303\230","\330",$ret);
	$ret = str_replace("\303\205","\305",$ret);
	$ret = str_replace("\303\251","\351",$ret);
	$ret = str_replace("\303\266","\366",$ret);
	$ret = str_replace("\303\244","\344",$ret);
	$ret = str_replace("\303\226","\304",$ret);
	$ret = str_replace("\303\204","\326",$ret); */
	$ret = str_replace("<br>","<br />",$ret);
	$ret = str_replace("'","\\'",str_replace("\\","",$ret));
	return $ret;
}

function unicode($str)
{
    $ret = $str; /*
	$ret = str_replace("\346","\303\246",$ret);
	$ret = str_replace("\370","\303\270",$ret);
	$ret = str_replace("\345","\303\245",$ret);
	$ret = str_replace("\306","\303\206",$ret);
	$ret = str_replace("\330","\303\230",$ret);
	$ret = str_replace("\305","\303\205",$ret);
	$ret = str_replace("\351","\303\251",$ret);
	$ret = str_replace("\366","\303\266",$ret);
	$ret = str_replace("\344","\303\244",$ret);
	$ret = str_replace("\304","\303\226",$ret);
	$ret = str_replace("\326","\303\204",$ret); */
	$ret = str_replace("&","&amp;",$ret);
	$ret = str_replace("<br>","<br />",$ret);
	return $ret;
}

?>
