<?php 
session_start();
$host = $_SERVER['SERVER_NAME'];
?>
<action id="dbaccess">
<table height="100%">
<tr>
 <td colspan="2"><div id="reload"></div></td>
</tr>
<tr>
<td>ftp host:</td><td><input type="text" name="host" value="<?= $host ?>"/></td>
</tr>
<tr>
<td>ftp port:</td><td><input type="text" name="port" value="21"/></td>
</tr>
<tr>
<td>DB name:</td><td><input type="text" name="db" value="ftp"/></td>
</tr>
<tr>
<td>Login table:</td><td><input type="text" name="login" value="ftpuser"/></td>
</tr>
<tr>
<td>user:</td><td><input type="text" name="user" /></td>
</tr>
<tr>
<td>pass:</td><td><input type="text" name="pass" /></td>
</tr>
<td colspan="2" align="center"><input type="button" value="Store FTP Info" onClick="submit_form('reload','dbaccess');" /></td>
</tr>
</table>
</action>
<script type="text/javascript">
  add_form('dbaccess','install/set_ftp.php','POST');
</script>