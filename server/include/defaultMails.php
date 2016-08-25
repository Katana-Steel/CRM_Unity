<?php
/**************************************************************************
    This file: ../web/helhed/include/defaultMails.php is part of Helhed Client.

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

$ret = $lst;
$ret[] = $tmp = user_m($usr,$link);
$sql = "select * from mail_rules";
$res = mysql_query($sql,$link);
echo "defaultMails: " . mysql_error($link)."\n";
while($r = mysql_fetch_assoc($res))
{
  if(($r["active"] == 0) || ($r["type"] != $toka)) continue;
  switch($r["conditions"]) {
  case "not usr":
    if($r["test_var"] != $usr) {
	  $tary = split("[,;]",$r["maillist"]);
	  $ret = array_merge($ret,$tary);
	}
    break;
  case "is usr":
    if($r["test_var"] == $usr) {
	  $tary = split("[,;]",$r["maillist"]);
	  $ret = array_merge($ret,$tary);
	}
    break;
  case "is lvl":
    if($r["test_var"] == $ulvl) {
	  $tary = split("[,;]",$r["maillist"]);
	  $ret = array_merge($ret,$tary);
	}
    break;
  case "in lst":
	$tary = split("[,;]",$r["maillist"]);
	if(in_array($tmp, $tary)) {
	  $ret = array_merge($ret,$tary);
	}
    break;
  case "default":
	$tary = split("[,;]",$r["maillist"]);
	  $ret = array_merge($ret,$tary);
    break;
  }
}

$lst = array_unique($ret);
?>
