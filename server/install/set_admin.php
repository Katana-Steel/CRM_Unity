<?php
session_start();

$_SESSION['dbhost'] = $_POST['host'];
$_SESSION['dbuser'] = $_POST['user'];
$_SESSION['dbpass'] = $_POST['pass'];
function getTz($str) {
    $ret = $str;
    $tz = array("PST8PDT","EST5EDT", "CST6CDT", "MST7MDT");
    foreach($tz as $t)
        if(stripos($t,$str) !== FALSE) {
            $ret = $t;
            break;
        }
    return $ret;
}
$d = date_create($_POST['dtime']);

$_SESSION['timezone'] = timezone_name_get(date_timezone_get($d));
 
 ?>
 <script type="text/javascript">
 ajax_loadContent('main_body','greet.php');
 </script>