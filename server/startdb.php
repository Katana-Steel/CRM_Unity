<?php
/* Autogenerated file from the Helhed installation */

$cust_table = "kunde";
$database = "helhed_test";
$failed = false;
$order_path = "/var/ftp/helhed";

function set_failed($link) {
    global $failed;
    $failed = true;
    mysql_close($link);
    return -1;
}

function dbcon()
{
	global $database, $failed;
	$link = mysql_connect("192.168.0.171","helhed","qwer") or die("connect... ". mysql_errno() .":". mysql_error());
	mysql_select_db($database,$link) or set_failed($link);
	if($failed) { $link = -1; $failed = false; }
	return $link;
}
?>