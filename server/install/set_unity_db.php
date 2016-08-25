<?php
session_start();

$_SESSION['unity_ctable'] = $_POST['ctable'];
$_SESSION['unity_db_name'] = $_POST['dbname'];
$_SESSION['unity_ftp_path'] = $_POST['updir'];

$_SESSION['unity_db_user'] = $_POST['user'];
$_SESSION['unity_db_pass'] = $_POST['pass'];


 ?>
 <script type="text/javascript">
 ajax_loadContent('main_body','greet.php');
 </script>
 