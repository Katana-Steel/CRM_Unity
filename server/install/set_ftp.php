<?php
session_start();

$_SESSION['v_ftp_host'] = $_POST['host'];
$_SESSION['v_ftp_port'] = $_POST['port'];
$_SESSION['v_ftp_db'] = $_POST['db'];
$_SESSION['v_ftp_login_table'] = $_POST['login'];

$_SESSION['v_ftp_user'] = $_POST['user'];
$_SESSION['v_ftp_pass'] = $_POST['pass'];


 ?>
 <script type="text/javascript">
 ajax_loadContent('main_body','greet.php');
 </script>