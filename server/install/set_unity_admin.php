<?php
session_start();

$_SESSION['crm_admin_user'] = $_POST['auser'];
$_SESSION['crm_admin_pass'] = $_POST['apass'];
$_SESSION['crm_admin_mail'] = $_POST['amail'];

 ?>
 <script type="text/javascript">
 ajax_loadContent('main_body','greet.php');
 </script>
 