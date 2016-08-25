<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/include.php is part of Helhed Server.

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
include_once('dinclude/vars.php');
include_once('html_mime_mail_2.5/htmlMimeMail.php');
include_once('dinclude/UserControl.php');
include_once('dinclude/startdb.htm');
include_once('dinclude/xml.php');
include_once('dinclude/unicode.php');

if(!isset($app)) $app = false;
function anti_hack() {
}

function align_KTilbud()
{
	$link = dbcon();
	$sql = "select * from `K-tilbud` where char_length(kunde_nr) > 7 group by kunde_nr";
	$res = mysql_query($sql,$link);
	if(mysql_num_rows($res) == 0) { mysql_close($link); return; }
	while($r = mysql_fetch_assoc($res)) {
		$d = mysql_fetch_row(mysql_query("select id from `keenan_kunde` where kundenr='".$r["kunde_nr"]."'",$link));
		mysql_query("update `K-tilbud` set kunde_nr='".$d[0]."' where kunde_nr='".$r["kunde_nr"]."'");
	}
	$fp = fopen("/var/www/lastAlignment","w");
	fwrite($fp,date("Dl \\t\h\e jS \of F Y"));
	fclose($fp);
	mysql_close($link);
}

function case_noid() {
anti_hack();
include('dinclude/case_noid.php');
}

function chklogin() {
anti_hack();
$ret = false;
include('dinclude/chklogin.php');
return $ret;
}

function chk_cid(&$cid) {
include('dinclude/chk_cid.php');
return $usr;
}

function clmn($nr) {
anti_hack();
include('dinclude/clmn.php');
return $str;
}

// this function removes any reoccuring data in an array.
function clr_dubs(&$ary){
include('dinclude/clr_dubs.php');
}

function complete_ord() {
anti_hack();
global $rpath;
include('dinclude/complete_ord.php');
}

function ctrcase() {
anti_hack();
include('dinclude/ctrcase.php');
}

function defaultMails(&$lst, $usr, $ulvl, $toka, $link) {
include('dinclude/defaultMails.php');
}

function dologin() {
anti_hack();
global $app;
include('dinclude/dologin.php');
}

function excel_out() {
anti_hack();
include('dinclude/excel_out.php');
}

function fetch_saelger($id,$link,$n='') {
include('dinclude/fetch_saelger.php');
if($n == '') {
 return user($r[0],$link);
} else {
 return $r[0];
}
}

function find_cases() {
anti_hack();
global $rpath;
include('dinclude/find_cases.php');
}

function get_nota() {
anti_hack();
global $rpath;
include('dinclude/get_nota.php');
}

function GetFK_OP($k_id,$link) {
include('dinclude/GetFK_OP.php');
return $tmp;
}

function GetK_OP($k_id,$link) {
include('dinclude/GetK_OP.php');
return $tmp;
}

function getmails() {
anti_hack();
global $rpath;
include('dinclude/getmails.php');
}

function getOID($kid,$type,$link) {
$oid = "";
include('dinclude/getOID.php');
return $oid;
}

function index() {
anti_hack();
global $rpath;
include('dinclude/index.php');
}

function info_text($type,$time) {
$ret = "";
include('dinclude/info_text.php');
return $ret;
}

function j_ins() {
anti_hack();
include('dinclude/j_ins.php');
}

function j_update() {
anti_hack();
include('dinclude/j_update.php');
}

function jour() {
anti_hack();
global $rpath;
include('dinclude/jour.php');
}

function jour_noid() {
anti_hack();
include('dinclude/jour_noid.php');
}

function kill_ord() {
anti_hack();
include('dinclude/kill_ord.php');
}

function killordm($nr,$title,$link) {
global $rpath;
include('dinclude/killordm.php');
return $ret;
}

function kj_seek() {
anti_hack();
global $month, $dary;
include('dinclude/kj_seek.php');
}

function ko_seek() {
anti_hack();
global $month, $dary;
include('dinclude/ko_seek.php');
}

function lev_test() {
anti_hack();
$ret = false;
include('dinclude/lev_test.php');
return $ret;
}

function lister() {
anti_hack();
global $rpath, $month;
include('dinclude/lister.php');
}

function login() {
include('dinclude/login.php');
}

function multi() {
anti_hack();
global $rpath;
include('dinclude/multi.php');
}

function multimail() {
anti_hack();
include('dinclude/multimail.php');
}

function NextJour() {
anti_hack();
include('dinclude/NextJour.php');
return $tmp + 1;
}

function newnota() {
anti_hack();
global $month,$dary;
include('dinclude/newnota.php');
}

function new_cus() {
anti_hack();
global $rpath;
include('dinclude/new_cus.php');
}

function nota() {
anti_hack();
global $month, $rpath;
include('dinclude/nota.php');
}

function o2a($type) {
anti_hack();
include('dinclude/o2a.php');
}

function ocase() {
anti_hack();
global $rpath;
include('dinclude/ocase.php');
}

function or_list() {
anti_hack();
global $rpath;
include('dinclude/list.php');
}

function ord_jour_dat() {
anti_hack();
global $month;
include('dinclude/ord_jour_dat.php');
}

function order_head($type,$id,$rek="",$machine="") {
include('dinclude/order_head.php');
}

function p_list() {
anti_hack();
global $month, $rpath;
include('dinclude/p_list.php');
}

function page_bottom() {
anti_hack();
include('dinclude/page_bottom.php');
}

function page_top($str,$id) {
anti_hack();
include('dinclude/page_top.php');
}

function placeord() {
anti_hack();
include('dinclude/placeord.php');
}

function printm($id,$type,$kid,$link) {
include('dinclude/printm.php');
return $ret;
}

function printp($id,$type,$kid,$link,$pre="no") {
anti_hack();
include('dinclude/printp.php');
}

function prnRestAccess($type=''){
include('dinclude/prnRestAccess.php');
}

function SetStatus($stat) {
anti_hack();
include('dinclude/SetStatus.php');
}
/*
function storeOID($id,$kid,$t,$link) {
include('dinclude/storeOID.php');
}
*/
function u_admin($link) {
include('dinclude/u_admin.php');
}

function uctr($link) {
include('dinclude/uctr.php');
}

function xml_admin($usr) {
include('dinclude/xml_admin.php');
}

function xml_create_jour($usr) {
include('dinclude/xml_create_jour.php');
}

function xml_create_order($usr,$file) {
include('dinclude/xml_create_order.php');
}

function xml_delivered($usr) {
include('dinclude/xml_delivered.php');
}

function xml_extra_mails($usr,$k_mails,$nr) {
include('dinclude/xml_extra_mails.php');
}

function xml_get_changed($save,$link) {
include('dinclude/xml_get_changed.php');
}

function xml_get_curlist($usr,$save,$knr,$link) {
include('dinclude/xml_get_curlist.php');
}

function xml_get_mails($usr) {
include('dinclude/xml_get_mails.php');
}

function xml_get_print($nr,$link) {
include('dinclude/xml_get_print.php');
}

function xml_get_temps($usr) {
include('dinclude/xml_get_temps.php');
}

function xml_get_xls($save,$link) {
include('dinclude/xml_get_xls.php');
}

function xml_gross_seek() {
include('dinclude/xml_gross_seek.php');
}

function xml_k_seek($usr) {
include('dinclude/xml_k_seek.php');
}

function xml_kill_ord($usr) {
include('dinclude/xml_kill_ord.php');
}

function xml_lvo($usr) {
include('dinclude/xml_lvo.php');
}

function xml_reenable($usr) {
include('dinclude/xml_reenable.php');
}

function xml_save_temp($usr) {
include('dinclude/xml_save_temp.php');
}

function xml_stat_list($usr) {
include('dinclude/xml_stat_list.php');
}

function xml_statistics($usr) {
include('dinclude/xml_statistics.php');
}

function xml_TOKA($nr) {
include('dinclude/xml_toka.php');
}

function xml_update_jour($usr) {
include('dinclude/xml_update_jour.php');
}
?>
