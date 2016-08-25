<?php
/**************************************************************************
    This file: ../web/helhed/include/include.php is part of Alchemiestick
    CRM Unity server.

    Helhed Client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009, 2010, 2012 René Kjellerup aka Katana Steel
**************************************************************************/

include_once('include/startdb.php');
include_once('html_mime_mail_2.5/htmlMimeMail.php');
include_once('include/UserControl.php');
include_once('include/xml.php');
include_once('unicode.php');

function align_KTilbud()
{
	$link = dbcon();
	$sql = "select * from `K-tilbud` where char_length(kunde_nr) > 7 group by kunde_nr";
	$res = mysql_query($sql,$link);
	if(mysql_num_rows($res) == 0) { mysql_close($link); return; }
	while($r = mysql_fetch_assoc($res)) {
		$d = mysql_fetch_row(mysql_query("select id from `kunde` where kundenr='".$r["kunde_nr"]."'",$link));
		mysql_query("update `K-tilbud` set kunde_nr='".$d[0]."' where kunde_nr='".$r["kunde_nr"]."'");
	}
	$fp = fopen("/var/www/lastAlignment","w");
	fwrite($fp,date("Dl \\t\h\e jS \of F Y"));
	fclose($fp);
	mysql_close($link);
}

function chk_cid(&$cid) {
include('include/chk_cid.php');
return $usr;
}

function defaultMails(&$lst, $usr, $ulvl, $toka, $link) {
include('include/defaultMails.php');
}

function dologin($link) {
include('include/dologin.php');
}

function GetFK_OP($k_id,$link) {
include('include/GetFK_OP.php');
return $tmp;
}

function getOID($kid,$type,$link) {
$oid = "";
include('include/getOID.php');
return $oid;
}

function info_text($type,$time) {
$ret = "";
include('include/info_text.php');
return $ret;
}

function killordm($nr,$title,$link) {
global $rpath;
include('include/killordm.php');
return $ret;
}

function order_head($type,$id,$rek="",$machine="") {
$ret = "";
include('include/order_head.php');
return $ret;
}

function page_bottom() {
$ret="";
include('include/page_bottom.php');
return $ret;
}

function page_top($str,$id) {
$ret = "";
include('include/page_top.php');
return $ret;
}

function printm($id,$type,$kid,$link) {
include('include/printm.php');
return $ret;
}

function printp($id,$type,$kid,$link,$pre="no") {
include('include/printp.php');
}

function xml_admin($usr) {
include('include/xml_admin.php');
}

function xml_create_jour($usr) {
include('include/xml_create_jour.php');
}

function xml_create_order($usr,$file) {
include('include/xml_create_order.php');
}

function xml_delivered($usr) {
include('include/xml_delivered.php');
}

function xml_extra_mails($usr,$k_mails,$nr) {
include('include/xml_extra_mails.php');
}

function xml_get_changed($save,$link) {
include('include/xml_get_changed.php');
}

function xml_get_curlist($usr,$save,$knr,$link) {
include('include/xml_get_curlist.php');
}

function xml_get_mails($usr) {
include('include/xml_get_mails.php');
}

function xml_get_print($nr,$link) {
include('include/xml_get_print.php');
}

function xml_get_temps($usr) {
include('include/xml_get_temps.php');
}

function xml_get_xls($save,$link) {
include('include/xml_get_xls.php');
}

function xml_gross_seek() {
include('include/xml_gross_seek.php');
}

function xml_k_seek($usr) {
include('include/xml_k_seek.php');
}

function xml_kill_ord($usr) {
include('include/xml_kill_ord.php');
}

function xml_lvo($usr) {
include('include/xml_lvo.php');
}

function xml_reenable($usr) {
include('include/xml_reenable.php');
}

function xml_rma($usr) {
include('include/xml_rma.php');
}

function xml_save_temp($usr) {
include('include/xml_save_temp.php');
}

function xml_stat_list($usr) {
include('include/xml_stat_list.php');
}

function xml_statistics($usr) {
include('include/xml_statistics.php');
}

function xml_TOKA($nr) {
include('include/xml_toka.php');
}

function xml_update_jour($usr) {
include('include/xml_update_jour.php');
}
?>
